/*
 * Copyright (c) 2014, Oculus VR, Inc.
 * All rights reserved.
 *
 * This source code is licensed under the BSD-style license found in the
 * LICENSE file in the root directory of this source tree. An additional grant
 * of patent rights can be found in the PATENTS file in the same directory.
 */
#include "RakThread.h"

#include "RakAssert.h"
#include "RakMemoryOverride.h"
#include "RakNetDefines.h"
#include "RakSleep.h"

using namespace RakNet;

#ifdef _WIN32

#include <stdio.h>

#ifndef _WIN32_WCE
#include <process.h>
#endif

#include <Windows.h>

int
RakThread::Create(
    RakThreadStartRoutine start_routine,
    void *arguments,
    int priority
) {
    #if defined _WIN32_WCE
    DWORD threadId;
    HANDLE handle = CreateThread(
        NULL, MAX_ALLOCA_STACK_ALLOCATION * 2,
        start_routine, arguments, 0, &threadId
    );
    #else
    unsigned int threadId;
    HANDLE handle = (HANDLE) _beginthreadex(
        NULL, MAX_ALLOCA_STACK_ALLOCATION * 2,
        start_routine, arguments, 0, &threadId
    );
    #endif

    if (!handle) {
        #if defined _WIN32_WCE
        RakAssert("CreateThread() in " __FILE__ " failed.");
        #else
        RakAssert("_beginthreadex() in " __FILE__ " failed.");
        #endif
        return 1;
    }

    /*
     * This could fail, but we don't care if it does. As such, no need to
     * check the return value as the thread has already been created.
     */
    SetThreadPriority(handle, priority);

    CloseHandle(handle);
    return 0;
}

#else

#include <pthread.h>

int
RakThread::Create(
    RakThreadStartRoutine start_routine,
    void *arguments,
    int priority
) {
    sched_param param;
    param.sched_priority = priority;

    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_attr_setschedparam(&attr, &param);
    pthread_attr_setstacksize(&attr, MAX_ALLOCA_STACK_ALLOCATION * 2);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);

    pthread_t handle;
    int result = pthread_create(&handle, &attr, start_routine, arguments);
    if (!result) {
        RakAssert("pthread_create() in " __FILE__ " failed.")
    }

    return result;
}

#endif
