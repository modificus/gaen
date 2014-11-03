//------------------------------------------------------------------------------
// InsertLightDirectionalMessage.h - Autogenerated message class for InsertLightDirectional
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

#ifndef GAEN_ENGINE_MESSAGES_INSERTLIGHTDIRECTIONALMESSAGE_H
#define GAEN_ENGINE_MESSAGES_INSERTLIGHTDIRECTIONALMESSAGE_H

#include "engine/MessageWriter.h"
#include "engine/math.h"
#include "engine/Color.h"
#include "core/threading.h"
#include "engine/Model.h"

namespace gaen
{
namespace messages
{

template <typename T>
class InsertLightDirectionalR
{
public:
    InsertLightDirectionalR(const T & msgAcc)
      : mMsgAcc(msgAcc)
    {

    }

    const Vec3 & direction() const { return *reinterpret_cast<const Vec3*>(&mMsgAcc[0].tCellPad.tCell); }
    Color color() const { return mMsgAcc[0].cells[3].color; }
    u32 uid() const { return mMsgAcc.message().payload.u; }
        
private:
    const T & mMsgAcc;


};

typedef InsertLightDirectionalR<MessageQueueAccessor> InsertLightDirectionalQR;
typedef InsertLightDirectionalR<MessageBlockAccessor> InsertLightDirectionalBR;

class InsertLightDirectionalQW : public MessageQueueWriter
{
public:
    InsertLightDirectionalQW(u32 msgId,
                             u32 flags,
                             task_id source,
                             task_id target,
                             u32 uid)
      : MessageQueueWriter(msgId,
                           flags,
                           source,
                           target,
                           to_cell(uid),
                           1)
    {}
    
    void setDirection(const Vec3 & val) { mMsgAcc[0].tCellPad.tCell = *reinterpret_cast<const tcell*>(&val); }
    void setColor(Color val) { mMsgAcc[0].cells[3].color = val; }
    void setUid(u32 val) { mMsgAcc.message().payload.u = val; }
};

class InsertLightDirectionalBW : public MessageBlockWriter
{
public:
    InsertLightDirectionalBW(u32 msgId,
                             u32 flags,
                             task_id source,
                             task_id target,
                             u32 uid)
      : MessageBlockWriter(msgId,
                           flags,
                           source,
                           target,
                           to_cell(uid),
                           1,
                           mBlocks)
    {}

    void setDirection(const Vec3 & val) { mMsgAcc[0].tCellPad.tCell = *reinterpret_cast<const tcell*>(&val); }
    void setColor(Color val) { mMsgAcc[0].cells[3].color = val; }
    void setUid(u32 val) { mMsgAcc.message().payload.u = val; }

private:
    Block mBlocks[1 + 1]; // +1 for header
};

} // namespace msg
} // namespace gaen

#endif // #ifndef GAEN_ENGINE_MESSAGES_INSERTLIGHTDIRECTIONALMESSAGE_H

