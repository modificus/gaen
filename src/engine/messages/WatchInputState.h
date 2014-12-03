//------------------------------------------------------------------------------
// WatchInputState.h - Autogenerated message class for WatchInputState
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

#ifndef GAEN_ENGINE_MESSAGES_WATCHINPUTSTATEMESSAGE_H
#define GAEN_ENGINE_MESSAGES_WATCHINPUTSTATEMESSAGE_H

#include "engine/MessageWriter.h"
#include "core/threading.h"
#include "engine/Model.h"

namespace gaen
{
namespace messages
{

template <typename T>
class WatchInputStateR
{
public:
    WatchInputStateR(const T & msgAcc)
      : mMsgAcc(msgAcc)
    {

    }

    u32 message() const { return mMsgAcc[0].cells[0].u; }
    u32 state() const { return mMsgAcc.message().payload.u; }
    u32 deviceId() const { return mMsgAcc[0].cells[1].u; }
        
private:
    const T & mMsgAcc;


};

typedef WatchInputStateR<MessageQueueAccessor> WatchInputStateQR;
typedef WatchInputStateR<MessageBlockAccessor> WatchInputStateBR;

class WatchInputStateQW : public MessageQueueWriter
{
public:
    WatchInputStateQW(u32 msgId,
                      u32 flags,
                      task_id source,
                      task_id target,
                      u32 state)
      : MessageQueueWriter(msgId,
                           flags,
                           source,
                           target,
                           to_cell(state),
                           1)
    {}
    
    void setMessage(u32 val) { mMsgAcc[0].cells[0].u = val; }
    void setState(u32 val) { mMsgAcc.message().payload.u = val; }
    void setDeviceId(u32 val) { mMsgAcc[0].cells[1].u = val; }
};

class WatchInputStateBW : public MessageBlockWriter
{
public:
    WatchInputStateBW(u32 msgId,
                      u32 flags,
                      task_id source,
                      task_id target,
                      u32 state)
      : MessageBlockWriter(msgId,
                           flags,
                           source,
                           target,
                           to_cell(state),
                           1,
                           mBlocks)
    {}

    void setMessage(u32 val) { mMsgAcc[0].cells[0].u = val; }
    void setState(u32 val) { mMsgAcc.message().payload.u = val; }
    void setDeviceId(u32 val) { mMsgAcc[0].cells[1].u = val; }

private:
    Block mBlocks[1 + 1]; // +1 for header
};

} // namespace msg
} // namespace gaen

#endif // #ifndef GAEN_ENGINE_MESSAGES_WATCHINPUTSTATEMESSAGE_H

