/*
 * Copyright (c) 2014, Oculus VR, Inc.
 * All rights reserved.
 *
 * This source code is licensed under the BSD-style license found in the
 * LICENSE file in the root directory of this source tree. An additional grant
 * of patent rights can be found in the PATENTS file in the same directory.
 */
#include "gettimeofday.h"

/*
 * This was originally taken from http://www.openasthra.com/c-tidbits/gettimeofday-function-for-windows/,
 * (before modification) but the link now seems to be dead. But now, at the time of writing, it points to
 * a gambling website.
 */

#if defined(_WIN32) && !defined(__GNUC__) && !defined(__GCCXML__)

#include "NativeTypes.h"
#include "WindowsIncludes.h"

#define DELTA_EPOCH_IN_MICROSECS 11644473600000000ULL

int
gettimeofday(struct timeval *tv, struct timezone *tz) {
    static bool initialized_tz = false;

    if (tv) {
        FILETIME ft;
        GetSystemTimeAsFileTime(&ft);

        uint64_t tmpres = 0;

        tmpres |= ft.dwHighDateTime;
        tmpres <<= 32;
        tmpres |= ft.dwLowDateTime;

        /* convert file time to unix epoch */
        tmpres /= 10; /* convert to microseconds */
        tmpres -= DELTA_EPOCH_IN_MICROSECS;
        tv->tv_sec = tmpres / 1000000UL;
        tv->tv_usec = tmpres % 1000000UL;
    }

    if (tz) {
        if (!initialized_tz) {
            _tzset();
            initialized_tz = true;
        }
        tz->tz_minuteswest = _timezone / 60;
        tz->tz_dsttime = _daylight;
    }

    return 0;
}

#endif /* defined(_WIN32) && !defined(__GNUC__)  &&!defined(__GCCXML__) */
