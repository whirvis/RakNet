/*
 * Copyright (c) 2014, Oculus VR, Inc.
 * All rights reserved.
 *
 * This source code is licensed under the BSD-style license found in the
 * LICENSE file in the root directory of this source tree. An additional grant
 * of patent rights can be found in the PATENTS file in the same directory.
 */
#ifndef RAKNET_THREAD_H
#define RAKNET_THREAD_H

#include "Export.h"
#include "WindowsIncludes.h"

/*
 * TODO: The whole point of RakThread is to allow for easy multiplatform
 *  thread creation, but defines different return values for start rotines
 *  on each different platform... Doesn't that defeat the entire point?
 * 
 * I really do not like the RAK_THREAD_DECLARATION define, it's completely
 * unnecessary should be replaced with a proper wrapper function used to
 * start all threads under RakNet.
 */
#if defined(_WIN32)
typedef unsigned (__stdcall *RakThreadStartRoutine)(void *);
#define RAK_THREAD_DECLARATION(_func) unsigned __stdcall _func(void *arguments)
#elif defined(_WIN32_WCE)
typedef LPTHREAD_START_ROUTINE RakThreadStartRoutine;
#define RAK_THREAD_DECLARATION(_func) DWORD WINAPI _func(LPVOID arguments)
#else
typedef void * (*RakThreadStartRoutine)(void *)
#define RAK_THREAD_DECLARATION(_func) void * _func(void *arguments)
#endif

namespace RakNet {

class RAK_DLL_EXPORT RakThread {
public:

    /*
     * TODO: All these methods are static and there's no instances...
     *  shouldn't RakThread be a namespace rather than a class ?
     */

    /*!
     * @brief
     * Creates a thread.
     *
     * @details
     * This is simplified to be cross platform, without all the extra junk.
     * Thread entrypoints can be declared via #RAK_THREAD_DECLARATION.
     *
     * Below is a table of some nice values for the priority parameter.
     * | Values         | Win32 priority                 |
     * | -------------- | ------------------------------ |
     * | `-20` to `-16` | `THREAD_PRIORITY_HIGHEST`      |
     * | `-15` to `-6`  | `THREAD_PRIORITY_ABOVE_NORMAL` |
     * | `-5`  to `+4`  | `THREAD_PRIORITY_NORMAL`       |
     * | `+5`  to `+14` | `THREAD_PRIORITY_BELOW_NORMAL` |
     * | `+15` to `+19` | `THREAD_PRIORITY_LOWEST`       |
     *
     * @param[in] start_routine The function from which to start the thread.
     * @param[in] arguments     The arguments to pass for creation.
     * @param[in] priority      The thread priority.
     *
     * @return Zero on success, anything else otherwise.
     */
    static int Create(
        RakThreadStartRoutine start_routine,
        void *arguments = nullptr,
        int priority = 0
     );

};

}

#endif /* RAKNET_THREAD_H */
