//------------------------------------------------------------------------------
// InsertTask.h - Autogenerated message class for InsertTask
//
// Gaen Concurrency Engine - http://gaen.org
// Copyright (c) 2014-2015 Lachlan Orr
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

#ifndef GAEN_ENGINE_MESSAGES_INSERTTASKMESSAGE_H
#define GAEN_ENGINE_MESSAGES_INSERTTASKMESSAGE_H

#include "engine/MessageWriter.h"
#include "engine/Task.h"
#include "core/threading.h"

namespace gaen
{
namespace messages
{

template <typename T>
class InsertTaskR
{
public:
    InsertTaskR(const T & msgAcc)
      : mMsgAcc(msgAcc)
    {
        if (&msgAcc[1] > &msgAcc[0])
        {
            // field is contiguous in ring buffer
            mpTask = reinterpret_cast<const Task*>(&msgAcc[0]);
        }
        else
        {
            // field wraps ring buffer, copy it into our datamember
            for (u32 i = 0; i < 2; ++i)
            {
                block_at(&mTask, i) = msgAcc[i + 0];
            }
            mpTask = &mTask;
        }

    }

    const Task & task() const { return *mpTask; }
    thread_id owner() const { return mMsgAcc.message().payload.u; }
        
private:
    const T & mMsgAcc;

    // These members provide storage for fields larger than a block that wrap the ring buffer
    Task mTask;
    const Task * mpTask;
};

typedef InsertTaskR<MessageQueueAccessor> InsertTaskQR;
typedef InsertTaskR<MessageBlockAccessor> InsertTaskBR;

class InsertTaskQW : public MessageQueueWriter
{
public:
    InsertTaskQW(u32 msgId,
                 u32 flags,
                 task_id source,
                 task_id target,
                 thread_id owner)
      : MessageQueueWriter(msgId,
                           flags,
                           source,
                           target,
                           to_cell(*reinterpret_cast<const u32*>(&owner)),
                           2)
    {}
    
    void setTask(const Task & val)
    {
        for (u32 i = 0; i < 2; ++i)
        {
            mMsgAcc[i + 0] = block_at(&val, i);
        }
    }
    void setOwner(thread_id val) { mMsgAcc.message().payload.u = val; }
};

class InsertTaskBW : public MessageBlockWriter
{
public:
    InsertTaskBW(u32 msgId,
                 u32 flags,
                 task_id source,
                 task_id target,
                 thread_id owner)
      : MessageBlockWriter(msgId,
                           flags,
                           source,
                           target,
                           to_cell(*reinterpret_cast<const u32*>(&owner)),
                           2,
                           mBlocks)
    {}

    void setTask(const Task & val)
    {
        for (u32 i = 0; i < 2; ++i)
        {
            mMsgAcc[i + 0] = block_at(&val, i);
        }
    }
    void setOwner(thread_id val) { mMsgAcc.message().payload.u = val; }

private:
    Block mBlocks[2 + 1]; // +1 for header
};

} // namespace msg
} // namespace gaen

#endif // #ifndef GAEN_ENGINE_MESSAGES_INSERTTASKMESSAGE_H

