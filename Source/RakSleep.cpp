/*
 * Copyright (c) 2014, Oculus VR, Inc.
 * All rights reserved.
 *
 * This source code is licensed under the BSD-style license found in the
 * LICENSE file in the root directory of this source tree. An additional grant
 * of patent rights can be found in the PATENTS file in the same directory.
 */
#include "RakSleep.h"

#if defined(_WIN32)

#include "WindowsIncludes.h"

void
RakSleep(unsigned int ms) {
    Sleep(ms);
}

#else

#include <pthread.h>
#include <sys/time.h>
#include <time.h>

void
RakSleep(unsigned int ms) {
    static pthread_cond_t waitCond = PTHREAD_COND_INITIALIZER;
    static pthread_mutex_t waitMutex = PTHREAD_MUTEX_INITIALIZER;

    /*
     * Single threaded sleep code thanks to Furquan Shaikh,
     * http://somethingswhichidintknow.blogspot.com/2009/09/sleep-in-pthread.html
     * This has been slightly modified from the original.
     */

    struct timeval now;
    gettimeofday(&now, NULL);

    long seconds = ms / 1000;
    long nanoseconds = (ms % 1000) * 1000000;

    struct timespec waitUntil;
    waitUntil.tv_sec = now.tv_sec + seconds;
    waitUntil.tv_nsec = (now.tv_usec * 1000) + nanoseconds;

    while (waitUntil.tv_nsec >= 1000000000) {
	waitUntil.tv_nsec -= 1000000000;
	waitUntil.tv_sec += 1;
    }

    pthread_mutex_lock(&waitMutex);
    pthread_cond_timedwait(&waitCond, &waitMutex, &waitUntil);
    pthread_mutex_unlock(&waitMutex);
}

#endif
