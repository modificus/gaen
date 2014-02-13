//------------------------------------------------------------------------------
// logging.cpp - Support for logging over udp to console listener
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

#include "core/stdafx.h"

#include <cstdarg>
#include <cstring>
#include <cstdio>
#include <algorithm>

#include "core/platutils.h"
#include "core/sockets.h"
#include "core/logging.h"

#include "core/log_message.h"

namespace gaen
{

void init_logging(const char * serverIp)
{
#if HAS(LOGGING)
    ASSERT(is_valid_ip(serverIp));
    u32 ip = str_to_ip(serverIp);
    singleton<Logger>().init(ip);
#endif
}

void fin_logging()
{
#if HAS(LOGGING)    
    singleton<Logger>().fin();
#endif
}


#if HAS(LOGGING)    


void log_failure(const char * msg)
{
    singleton<Logger>().log(kLS_Error, msg);
}

void Logger::init(u32 serverIp)
{
    ASSERT(!mIsInit);
    bool ret = sock_create(&mSock);
    ASSERT(ret);
    mServerIp = serverIp;
    set_report_failure_cb(log_failure);
    mIsInit = true;
}

void Logger::fin()
{
    ASSERT(mIsInit);
    sock_close(mSock);
    mIsInit = false;
}

void Logger::log(LogSeverity severity, const char * message)
{
    ASSERT(mIsInit);
    ASSERT(message);

    thread_local LogMessage tLogMessage;

    tLogMessage.header.time = now();
    tLogMessage.header.sev = severity;

    size_t msgLen = std::max(kMaxLogMessageSize-1, strlen(message) + 1);
    strncpy(tLogMessage.msg, message, msgLen-1);
    tLogMessage.msg[msgLen-1] = '\0';

    sock_sendto(mSock,
                reinterpret_cast<u8*>(&tLogMessage),
                sizeof(LogMessageHeader) + msgLen,
                mServerIp,
                kLoggingPort);
}

void logf(LogSeverity severity, const char * format, ...)
{
    if (!singleton<Logger>().isInit())
    {
        // This condition isn't a failure, it just means logging
        // wasn't enabled when gaen was started.
        return;
    }

    thread_local char tMessage[kMaxLogMessageSize];

    va_list argptr;
    va_start(argptr, format);

    if (format && format[0] != '\0')
    {
        int ret = vsnprintf(tMessage, kMaxLogMessageSize-1, format, argptr);
        
        if (ret <= 0)
        {
            strncpy(tMessage, "logf was unable to format message", kMaxLogMessageSize-1);
        }
    }
    else
        tMessage[0] = '\0';
    
    va_end(argptr);

    tMessage[kMaxLogMessageSize-1] = '\0'; 

    singleton<Logger>().log(severity, tMessage);
}

#endif // #if HAS(LOGGING)

}
