/*
 * Copyright (c) 2014, Oculus VR, Inc.
 * All rights reserved.
 *
 * This source code is licensed under the BSD-style license found in the
 * LICENSE file in the root directory of this source tree. An additional grant
 * of patent rights can be found in the PATENTS file in the same directory.
 */
#ifndef RAKNET_GET_TIME_OF_DAY_H
#define RAKNET_GET_TIME_OF_DAY_H

#if defined(_WIN32) && !defined(__GNUC__) && !defined(__GCCXML__)

#include <time.h>

struct timezone {
    int tz_minuteswest; /* minutes W of Greenwich */
    int tz_dsttime;     /* type of dst correction */
};

int gettimeofday(struct timeval *tv, struct timezone *tz);

#else

#include <sys/time.h>
#include <unistd.h>

/*
 * Uncomment the code below if necessary (you can do this with CTRL+K+U in Visual Studio).
 * This was originally taken from http://www.halcode.com/archives/2008/08/26/retrieving-system-time-gettimeofday/,
 * (before modification) but the link now goes to a 404 page after redirecting to a completely different domain.
 */

//struct timezone {
//    int tz_minuteswest;
//    int tz_dsttime;
//};
//
//#ifdef __cplusplus
//
///*
// * Don't use a define here, otherwise anyone including this file
// * will have this defined even if they don't want or need it.
// */
//static const int DELTA_EPOCH_IN_MICROSECS = 11644473600000000ULL;
//
//void GetSystemTimeAsFileTime(FILETIME *);
//
//inline int
//gettimeofday(struct timeval *p, void *tz) {
//    union {
//        long long ns100; /* time since 1 Jan 1601 in 100ns units */
//        FILETIME ft;
//    } now;
//
//    GetSystemTimeAsFileTime(&now.ft);
//    p->tv_usec = (now.ns100 / 10LL) % 1000000LL;
//    p->tv_sec = (now.ns100 - DELTA_EPOCH_IN_MICROSECS) / 10000000LL;
//    
//    return 0;
//}
// 
//#else
//
//int gettimeofday(struct timeval *p, void *tz);
//
//#endif /* __cplusplus */

#endif /* defined(_WIN32) && !defined(__GNUC__) && !defined(__GCCXML__) */

#endif /* RAKNET_GET_TIME_OF_DAY_H */
