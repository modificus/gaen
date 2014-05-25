//------------------------------------------------------------------------------
// InsertTaskMessage.h - Autogenerated message class for InsertTask
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

#ifndef GAEN_ENGINE_MESSAGES_INSERTTASKMESSAGE_H
#define GAEN_ENGINE_MESSAGES_INSERTTASKMESSAGE_H

#include "engine/MessageWriter.h"
#include "core/threading.h"
#include "engine/Task.h"

namespace gaen
{

class InsertTaskMsgR
{
public:
    InsertTaskMsgR(const MessageQueue::MessageAccessor & msgAcc)
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

    thread_id owner() const { return mMsgAcc.message().payload.u; }
    const Task & task() const { return *mpTask; }
        
private:
    const MessageQueue::MessageAccessor & mMsgAcc;

    // These members provide storage for fields larger than a block that wrap the ring buffer
    Task mTask;
    const Task * mpTask;    
};



class InsertTaskMsgW : protected MessageWriter
{
public:
    InsertTaskMsgW(u32 msgId,
                   u32 flags,
                   task_id source,
                   task_id target,
                     thread_id owner)
      : MessageWriter(msgId,
                      flags,
                      source,
                      target,
                      to_cell(owner),
                      2) {}
    
    void setOwner(thread_id val) { mMsgAcc.message().payload.u = val; }
    void setTask(const Task & val)
    {
        for (u32 i = 0; i < 2; ++i)
        {
            mMsgAcc[i + 0] = block_at(&val, i);
        }
    }
};

} // namespace gaen

#endif // #ifndef GAEN_ENGINE_MESSAGES_INSERTTASKMESSAGE_H

