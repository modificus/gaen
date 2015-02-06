//------------------------------------------------------------------------------
// threading.cpp - Wrapper of C++ threads which manages Gaen thread specifics
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

#include "core/stdafx.h"

#include <cstring>
#include <atomic>

#include "core/thread_local.h"
#include "core/logging.h"
#include "core/threading.h"

namespace gaen
{

static thread_id sNumThreads = 0;
static bool sIsThreadingInit = false;

static ThreadInfo sThreadInfos[kMaxThreads];

// Thread local variables
TL(thread_id, tThreadId) = kInvalidThreadId;


static thread_id next_available_thread_id()
{
    static thread_id sNextId = 0;
    thread_id nextId = sNextId++;
    ASSERT(nextId >= 0 && nextId < sNumThreads);
    return nextId;
}

void init_threading(thread_id numThreads)
{
    ASSERT(!sIsThreadingInit);
    ASSERT(numThreads >= kMinThreads &&
           numThreads <= core_count() &&
           numThreads <= kMaxThreads);
    ASSERT(sNumThreads == 0);

    sNumThreads = numThreads;

    // We should have been called from the main thread, so we need to register her.
    sIsThreadingInit = true;

    // Init our main thread.
    // The main thread doesn't run a TaskMaster, but it
    // needs to be identified with a unique thread_id.
    ASSERT(tThreadId == kInvalidThreadId);
    tThreadId = kMainThreadId;
}

void fin_threading()
{
    ASSERT(sIsThreadingInit);

    // LORRTODO - join threads
}

bool is_threading_init()
{
    return sIsThreadingInit;
}

inline thread_id num_threads()
{
    return sNumThreads;
}

thread_id active_thread_id()
{
    ASSERT_MSG(tThreadId != kInvalidThreadId, "Main thread has not been initialized, or this thread wasn't created properly with gaen::start_thread");
    return tThreadId;
}

ThreadInfo & active_thread_info()
{
    ASSERT_MSG(tThreadId != kInvalidThreadId, "Main thread has not been initialized, or this thread wasn't created properly with gaen::start_thread");
    ThreadInfo & ti = sThreadInfos[tThreadId];
    ASSERT(ti.threadId == tThreadId &&
           ti.threadId != kInvalidThreadId);
    return ti;
}

void set_active_thread_id(thread_id tid)
{
    ASSERT_MSG(tThreadId == kInvalidThreadId, "Someone has tried to set a thread_id when the thread appears to already have been initialized");
    tThreadId = tid;
}

ThreadInfo & init_main_thread()
{
    ThreadInfo & ti = init_thread();

    ASSERT(ti.threadId == 0);
    ti.isRunning = true;
    set_active_thread_id(ti.threadId);

    return ti;
}

ThreadInfo & init_thread()
{
    ASSERT(is_threading_init());

    thread_id tid = next_available_thread_id();

    ThreadInfo & ti = sThreadInfos[tid];
    ASSERT(ti.threadId == kInvalidThreadId &&
           !ti.isRunning);
    ti.threadId = tid;

    return ti;
}

void fin_thread()
{
    // LORRTODO - determine if we need this method
    LOG_INFO("fin_thread() currently does nothing");
}

void join_all_threads()
{
    for (thread_id tid = 0; tid < num_threads(); ++tid)
    {
        ThreadInfo & ti = sThreadInfos[tid];
        ti.thread.join();        
    }
}


} // namespace gaen


