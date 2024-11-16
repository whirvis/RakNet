/*
 * Copyright (c) 2014, Oculus VR, Inc.
 * All rights reserved.
 *
 * This source code is licensed under the BSD-style license found in the
 * LICENSE file in the root directory of this source tree. An additional grant
 * of patent rights can be found in the PATENTS file in the same directory.
 */
#include "RakNetTime.h"

#define US_MILLION            ((RakNet::TimeUS) 1000000)
#define RAKNET_TIME_HALF_SPAN (((RakNet::Time) -1) / ((RakNet::Time) 2));

#if defined(GET_TIME_SPIKE_LIMIT) && GET_TIME_SPIKE_LIMIT > 0

#include "SimpleMutex.h"

#define NORMALIZE_TIME_IF_NEEDED(_time) NormalizeTime((_time))

/*
 * This constraints the timer forward jump to one second, and prevents it
 * from jumping backwards. See http://support.microsoft.com/kb/274323 for
 * more information.
 * 
 * This also has the effect where debugging a sending system won't treat the
 * time spent while halted as more than one second as the elapsed time.
 */
static RakNet::TimeUS
NormalizeTime(RakNet::TimeUS time) {
    static RakNet::SimpleMutex mutex;
    
    static RakNet::TimeUS lastNormalizedInput = 0;
    static RakNet::TimeUS lastNormalizedOutput = 0;
    
    mutex.Lock();
    if (time >= lastNormalizedInput) {
        RakNet::TimeUS diff = time - lastNormalizedInput;
        if (diff > GET_TIME_SPIKE_LIMIT) {
            lastNormalizedOutput += GET_TIME_SPIKE_LIMIT;
        } else {
            lastNormalizedOutput += diff;
        }
    } else {
        lastNormalizedOutput += GET_TIME_SPIKE_LIMIT;
    }

    lastNormalizedInput = time;
    RakNet::TimeUS output = lastNormalizedOutput;
    mutex.Unlock();

    return output;
}

#else

#define NORMALIZE_TIME_IF_NEEDED(_time) (_time)

#endif /* defined(GET_TIME_SPIKE_LIMIT) && GET_TIME_SPIKE_LIMIT > 0 */

RakNet::Time
RakNet::GetTime() {
    return GetTimeUS() / 1000;
}

RakNet::TimeMS
RakNet::GetTimeMS() {
    return GetTimeUS() / 1000;
}

#if defined(_WIN32)

#include "WindowsIncludes.h"

RakNet::TimeUS
RakNet::GetTimeUS() {
    /*
     * QueryPerformanceFrequency must be called each time, as the CPU
     * clock speeds can change during runtime (particularly in regions
     * such as China when running LuDaShi).
     */
    LARGE_INTEGER freq;
    QueryPerformanceFrequency(&freq);
    LARGE_INTEGER counter;
    QueryPerformanceCounter(&counter);

    LONGLONG quotient = counter.QuadPart / freq.QuadPart;
    LONGLONG remainder = counter.QuadPart % freq.QuadPart;
    RakNet::TimeUS currentTime =
        (quotient * US_MILLION + (remainder * US_MILLION / freq.QuadPart));

    return NORMALIZE_TIME_IF_NEEDED(currentTime);
}

#elif defined(__GNUC__) || defined(__GCCXML__)

#include <sys/time.h>
#include <unistd.h>

static RakNet::TimeUS initialTime = 0;

RakNet::TimeUS
RakNet::GetTimeUS() {
    timeval tv;

    /*
     * This is done since otherwise RakNet::Time in milliseconds
     * won't work, as it will underflow when dividing by 1000 to
     * do the conversion.
     */
    if (initialTime == 0) {
        gettimeofday(&tv, 0);
        initialTime = tv.tv_sec * US_MILLION + tv.tv_usec;
    }

    gettimeofday(&tv, 0);
    RakNet::TimeUS currentTime = tv.tv_sec * US_MILLION + tv.tv_usec;

    return NORMALIZE_TIME_IF_NEEDED(currentTime - initialTime);
}

#endif

bool
RakNet::GreaterThan(RakNet::Time a, RakNet::Time b) {
    return b != a && b - a > RAKNET_TIME_HALF_SPAN;
}

bool
RakNet::LessThan(RakNet::Time a, RakNet::Time b) {
    return b != a && b - a < RAKNET_TIME_HALF_SPAN;
}
