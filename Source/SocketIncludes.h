/*
 * Copyright (c) 2014, Oculus VR, Inc.
 * All rights reserved.
 *
 * This source code is licensed under the BSD-style license found in the
 * LICENSE file in the root directory of this source tree. An additional grant
 * of patent rights can be found in the PATENTS file in the same directory.
 */
#ifndef RAKNET_SOCKET_INCLUDES_H
#define RAKNET_SOCKET_INCLUDES_H

/*
 * TODO: This is temporary, remove this as soon as all other mentions of
 *  _PP_Instance have been fully stripped from the codebase.
 */
#define _PP_Instance_ int

#if defined(_WIN32)
    /*
     * Note that IP_DONTFRAGMENT is different between WinSock 1 and WinSock 2.
     * Therefore, WinSock2.h must be linked against Ws2_32.lib and WinSock.h
     * must be linked against WSock32.lib. If the two are mixed up, this flag
     * won't work correctly!
     * 
     * WinRT:  http://msdn.microsoft.com/en-us/library/windows/apps/windows.networking.sockets
     * Sample: http://stackoverflow.com/questions/10290945/correct-use-of-udp-datagramsocket
     */

    #include <winsock2.h>

    typedef SOCKET __UDPSOCKET__;
    typedef SOCKET __TCPSOCKET__;
    typedef int socklen_t;
#else
    #define closesocket close

    #include <unistd.h>
    #include <sys/types.h>
    #include <sys/socket.h>
    #include <netinet/in.h>
    #include <arpa/inet.h>
    #include <unistd.h>
    #include <fcntl.h>

    /* Unix & Linux use ints for sockets */
    typedef int __UDPSOCKET__;
    typedef int __TCPSOCKET__;
#endif

#endif  /* RAKNET_SOCKET_INCLUDES_H */
