//------------------------------------------------------------------------------
// MouseMove.h - Autogenerated message class for MouseMove
//
// Gaen Concurrency Engine - http://gaen.org
// Copyright (c) 2014-2016 Lachlan Orr
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

#ifndef GAEN_ENGINE_MESSAGES_MOUSEMOVEMESSAGE_H
#define GAEN_ENGINE_MESSAGES_MOUSEMOVEMESSAGE_H

#include "engine/MessageWriter.h"
#include "core/threading.h"
#include "engine/Task.h"
#include "engine/Model.h"

namespace gaen
{
namespace messages
{

template <typename T>
class MouseMoveR
{
public:
    MouseMoveR(const T & msgAcc)
      : mMsgAcc(msgAcc)
    {

    }

    u32 xDelta() const { return (u32)mMsgAcc.message().payload.u; }
    u32 yDelta() const { return mMsgAcc[0].cells[0].u; }
        
private:
    const T & mMsgAcc;


};

typedef MouseMoveR<MessageQueueAccessor> MouseMoveQR;
typedef MouseMoveR<MessageBlockAccessor> MouseMoveBR;

class MouseMoveQW : public MessageQueueWriter
{
public:
    MouseMoveQW(u32 msgId,
                u32 flags,
                task_id source,
                task_id target,
                u32 xDelta)
      : MessageQueueWriter(msgId,
                           flags,
                           source,
                           target,
                           to_cell(xDelta),
                           1)
    {}
    
    void setXDelta(u32 val) { mMsgAcc.message().payload.u = (u32)val; }
    void setYDelta(u32 val) { mMsgAcc[0].cells[0].u = val; }
};

class MouseMoveBW : public MessageBlockWriter
{
public:
    MouseMoveBW(u32 msgId,
                u32 flags,
                task_id source,
                task_id target,
                u32 xDelta)
      : MessageBlockWriter(msgId,
                           flags,
                           source,
                           target,
                           to_cell(xDelta),
                           1,
                           mBlocks)
    {}

    void setXDelta(u32 val) { mMsgAcc.message().payload.u = (u32)val; }
    void setYDelta(u32 val) { mMsgAcc[0].cells[0].u = val; }

private:
    Block mBlocks[1 + 1]; // +1 for header
};

} // namespace msg
} // namespace gaen

#endif // #ifndef GAEN_ENGINE_MESSAGES_MOUSEMOVEMESSAGE_H

