//------------------------------------------------------------------------------
// InsertModelInstance.h - Autogenerated message class for InsertModelInstance
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

#ifndef GAEN_ENGINE_MESSAGES_INSERTMODELINSTANCEMESSAGE_H
#define GAEN_ENGINE_MESSAGES_INSERTMODELINSTANCEMESSAGE_H

#include "engine/MessageWriter.h"
#include "engine/math.h"
#include "core/threading.h"
#include "engine/Model.h"

namespace gaen
{
namespace messages
{

template <typename T>
class InsertModelInstanceR
{
public:
    InsertModelInstanceR(const T & msgAcc)
      : mMsgAcc(msgAcc)
    {
        if (&msgAcc[2] > &msgAcc[0])
        {
            // field is contiguous in ring buffer
            mpTransform = reinterpret_cast<const Mat34*>(&msgAcc[0]);
        }
        else
        {
            // field wraps ring buffer, copy it into our datamember
            for (u32 i = 0; i < 3; ++i)
            {
                block_at(&mTransform, i) = msgAcc[i + 0];
            }
            mpTransform = &mTransform;
        }

    }

    const Mat34 & transform() const { return *mpTransform; }
    Model * model() const { return static_cast<Model *>(mMsgAcc[3].dCells[0].p); }
    u32 uid() const { return mMsgAcc.message().payload.u; }
    bool isAssetManaged() const { return mMsgAcc[3].cells[2].b; }
        
private:
    const T & mMsgAcc;

    // These members provide storage for fields larger than a block that wrap the ring buffer
    Mat34 mTransform;
    const Mat34 * mpTransform;
};

typedef InsertModelInstanceR<MessageQueueAccessor> InsertModelInstanceQR;
typedef InsertModelInstanceR<MessageBlockAccessor> InsertModelInstanceBR;

class InsertModelInstanceQW : public MessageQueueWriter
{
public:
    InsertModelInstanceQW(u32 msgId,
                          u32 flags,
                          task_id source,
                          task_id target,
                          u32 uid)
      : MessageQueueWriter(msgId,
                           flags,
                           source,
                           target,
                           to_cell(uid),
                           4)
    {}
    
    void setTransform(const Mat34 & val)
    {
        for (u32 i = 0; i < 3; ++i)
        {
            mMsgAcc[i + 0] = block_at(&val, i);
        }
    }
    void setModel(Model * pVal) { mMsgAcc[3].dCells[0].p = pVal; }
    void setUid(u32 val) { mMsgAcc.message().payload.u = val; }
    void setIsAssetManaged(bool val) { mMsgAcc[3].cells[2].b = val; }
};

class InsertModelInstanceBW : public MessageBlockWriter
{
public:
    InsertModelInstanceBW(u32 msgId,
                          u32 flags,
                          task_id source,
                          task_id target,
                          u32 uid)
      : MessageBlockWriter(msgId,
                           flags,
                           source,
                           target,
                           to_cell(uid),
                           4,
                           mBlocks)
    {}

    void setTransform(const Mat34 & val)
    {
        for (u32 i = 0; i < 3; ++i)
        {
            mMsgAcc[i + 0] = block_at(&val, i);
        }
    }
    void setModel(Model * pVal) { mMsgAcc[3].dCells[0].p = pVal; }
    void setUid(u32 val) { mMsgAcc.message().payload.u = val; }
    void setIsAssetManaged(bool val) { mMsgAcc[3].cells[2].b = val; }

private:
    Block mBlocks[4 + 1]; // +1 for header
};

} // namespace msg
} // namespace gaen

#endif // #ifndef GAEN_ENGINE_MESSAGES_INSERTMODELINSTANCEMESSAGE_H

