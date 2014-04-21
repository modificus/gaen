//------------------------------------------------------------------------------
// Task.h - Base definition of an updatable task
//
// Gaen Concurrency Engine - http://gaen.org
// Copyright (c) 2014 Lachlan Orr
//
// This software is provided 'as-is', without any express or implied
// warranty. In no event will the authors be held liable for any damages
// arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it
// freely, subject to the following restrictions:
//
//   1. The origin of this software must not be misrepresented; you must not
//   claim that you wrote the original software. If you use this software
//   in a product, an acknowledgment in the product documentation would be
//   appreciated but is not required.
//
//   2. Altered source versions must be plainly marked as such, and must not be
//   misrepresented as being the original software.
//
//   3. This notice may not be removed or altered from any source
//   distribution.
//------------------------------------------------------------------------------

#ifndef GAEN_ENGINE_TASK_H
#define GAEN_ENGINE_TASK_H

#include "core/base_defines.h"
#include "engine/MessageQueue.h"

namespace gaen
{

// We only have 28 bits per task_id inside of the Task and Message structures.
// If you change the size in either of those structs, all of them must change.
static const task_id kMaxTaskId = (2 << 28) - 1;

// LORRTODO - do we still need this kRootTaskId?  We're no longer doing the tree thing
static const task_id kRootTaskId         = 0; // A task with this as their parent is a top level, root task
static const task_id kInvalidTaskId      = kMaxTaskId - 0; // 536870911

static const task_id kMainThreadTaskId   = kMaxTaskId - 1; // 536870910, special task id used to refer to the main thread as a task

static const task_id kRendererTaskId     = kMaxTaskId - 3; // 536870908
static const task_id kInputManagerTaskId = kMaxTaskId - 4;  // 536870907

enum class TaskStatus : u8
{
    Initializing = 0,
    Paused,
    Running,
    Dead
};

enum class TaskPermissions : u8
{
    Private = 0,
    Group,
    Guild,
    Public
};

// Return the next globally unique task id
task_id next_task_id();

//------------------------------------------------------------------------------
// Tasks are the base work unit for the TaskMaster scheduler.
// They're small (32 bytes) and can be stored contiguously to iterate over
// them in a cache friendly fashion.
//
// Usage:
//   pObj must implement methods:
//     void update(f32 deltaSecs);
//     // Queue Message
//     MessageResult message(const Message & msg, const MessageQueue::MessageAccessor& msgAcc);
//     // Immediate Message
//     MessageResult message(const Message & msg, const MessageBlock* pBlocks);
//     void setTaskId(task_id taskId);
//
// E.g.
//   Task t = Task::create(pObj);
//   
//
// Instead of an object hierarchy with virtual methods for update and
// message functions, we opt for this delegate'ish approach. It
// eliminates at a dereference on each, call to update() and message()
// methods. It also alows us to aggregate tasks in data structures
// even though they don't share any type similarities except for the
// loose duck typing of the required methods.
//
// This can be thought of as a special case delegate with three methods,
// modeled after Sergey Ryazanov's Impossibly Fast C++ Delegates
// article at:
// http://www.codeproject.com/Articles/11015/The-Impossibly-Fast-C-Delegates
//------------------------------------------------------------------------------
struct Task
{
public:
    Task() = default;

    template <class T>
    static Task create(T* pThat)
    {
        Task task;

        task.mStatus = static_cast<u8>(TaskStatus::Initializing);
        task.mPermissions = 0;
        task.mTaskId = next_task_id();

        pThat->setTaskId(task.mTaskId);

        task.mUNUSED = 0xDEADbeef;

        task.mpThat = pThat;

        task.mpMessageStub = &message_stub<T>;
        MessageImmediateStub messageImmediateStub = &message_immediate_stub<T>;

        std::intptr_t iptrMessageStub = reinterpret_cast<std::intptr_t>(task.mpMessageStub);
        std::intptr_t iptrMessageImmediateStub = reinterpret_cast<std::intptr_t>(messageImmediateStub);

        // We only store one real function pointer to the stubs, and
        // the others are offsets to this pointer.  This allows us to
        // use 8 bytes for the first, but only 4 bytes each for each
        // additional message.
        task.mMessageImmediateStubOffset = static_cast<i32>(iptrMessageImmediateStub - iptrMessageStub);

        // Not all tasks are updatable.  To create an updatable one,
        // use createUpdatable static function below.
        task.mUpdateStubOffset = 0;

        return task;
    }

    template <class T>
    static Task createUpdatable(T* pThat)
    {
        Task task = Task::create(pThat);

        // This task is updatable, so calculate the offset to that method as well.
        std::intptr_t iptrMessageStub = reinterpret_cast<std::intptr_t>(task.mpMessageStub);
        UpdateStub updateStub = &update_stub<T>;
        std::intptr_t iptrUpdateStub = reinterpret_cast<std::intptr_t>(updateStub);
        task.mUpdateStubOffset = static_cast<i32>(iptrUpdateStub - iptrMessageStub);
        
        return task;
    }

    task_id id() const { return mTaskId; }

    TaskStatus status() const { return static_cast<TaskStatus>(mStatus); }
    void setStatus(TaskStatus newStatus) { mStatus = static_cast<u8>(newStatus); }

    TaskPermissions permissions() const { return static_cast<TaskPermissions>(mPermissions); }
    void setPermissions(TaskPermissions newPermissions) { mPermissions = static_cast<u8>(newPermissions); }

    void * that() { return mpThat; }
    const void * that() const { return mpThat; }

    // Queued message
    MessageResult message(const Message & msg, const MessageQueue::MessageAccessor& msgAcc)
    {
        return (*mpMessageStub)(mpThat, msg, msgAcc);
    }

    // Immediate message
    MessageResult message(const Message & msg, const MessageBlock * pBlocks)
    {
        // Since we're storing the offset of the message stub from the
        // update stub we do a little pointer arithmetic to get the
        // actual address.

        std::intptr_t iptrMessageStub = reinterpret_cast<std::intptr_t>(mpMessageStub);
        std::intptr_t iptrMessageImmediateStub = iptrMessageStub + mMessageImmediateStubOffset;

        MessageImmediateStub pMessageImmediateStub = reinterpret_cast<MessageImmediateStub>(iptrMessageImmediateStub);
        return (*pMessageImmediateStub)(mpThat, msg, pBlocks);
    }

    void update(f32 deltaSecs)
    {
        // Since we're storing the offset of the message stub from the
        // update stub we do a little pointer arithmetic to get the
        // actual address.

        if (mUpdateStubOffset != 0) // some tasks are not updatable
        {
            std::intptr_t iptrMessageStub = reinterpret_cast<std::intptr_t>(mpMessageStub);
            std::intptr_t iptrUpdateStub = iptrMessageStub + mUpdateStubOffset;
        
            UpdateStub pUpdateStub = reinterpret_cast<UpdateStub>(iptrUpdateStub);
            (*pUpdateStub)(mpThat, deltaSecs);
        }
    }


private:
    typedef void (*UpdateStub)(void*, f32);

    // Message coming from the processing of a MessageQueue
    typedef MessageResult (*MessageStub)(void*, const Message&, const MessageQueue::MessageAccessor&);

    // Message coming from someone for immediate processing (no MessageQueue access)
    typedef MessageResult (*MessageImmediateStub)(void*, const Message&, const MessageBlock*);


    u32 mStatus:2;           // current running state
    u32 mPermissions:2;      // permissions for others to send messages
    u32 mTaskId:28;          // our task id - NOTE Changeing this size requires changing kMaxTaskId in Task.h

    u32 mUNUSED;             // LORRTODO FIND SOMETHING USEFUL TO DO WITH THIS 32 BITS

    MessageStub mpMessageStub;        // address of message method
    i32 mMessageImmediateStubOffset; // offset in bytes from MessageStub pointer to MessageImmediateStub pointer
    i32 mUpdateStubOffset;           // offset in bytes from MessageStub pointer to UpdateStub pointer

    void* mpThat;                     // pointer to class instance that has the real update/message methods

    template <class T>
    static void update_stub(void* pThat, f32 deltaSecs)
    {
        T* p = static_cast<T*>(pThat);
        p->update(deltaSecs);
    }

    template <class T>
    static MessageResult message_stub(void* pThat, const Message& msg, const MessageQueue::MessageAccessor& msgAcc)
    {
        T* p = static_cast<T*>(pThat);
        return p->message(msg, msgAcc);
    }

    template <class T>
    static MessageResult message_immediate_stub(void* pThat, const Message& msg, const MessageBlock* pBlocks)
    {
        T* p = static_cast<T*>(pThat);
        return p->message(msg, pBlocks);
    }
};

// We make assumptions about this size, like alignment, pass by value, et al.
// If the size needs to change in future, care must be taken to re-assess these
// assumptions as they appear throughout the code.
static_assert(sizeof(Task)==32, "Task should be 32 bytes");

} // namespace gaen

#endif // #ifndef GAEN_ENGINE_TASK_H
