/*
 * Copyright (c) 2014, Oculus VR, Inc.
 * All rights reserved.
 *
 * This source code is licensed under the BSD-style license found in the
 * LICENSE file in the root directory of this source tree. An additional grant
 * of patent rights can be found in the PATENTS file in the same directory.
 */
#ifdef _WIN32

/*
 * WinSock2.h must be included before Windows.h, otherwise we'll get compiler
 * errors related to type re-definition.
 * ```
 * winsock2.h(99) : error C2011: 'fd_set' : 'struct' type redefinition
 * winsock2.h(134) : warning C4005: 'FD_SET' : macro redefinition
 * winsock.h(83) : see previous definition of 'FD_SET'
 * winsock2.h(143) : error C2011: 'timeval' : 'struct' type redefinition
 * winsock2.h(199) : error C2011: 'hostent' : 'struct' type redefinition
 * winsock2.h(212) : error C2011: 'netent' : 'struct' type redefinition
 * winsock2.h(219) : error C2011: 'servent' : 'struct' type redefinition
 * ```
 */

#include <WinSock2.h>
#include <Windows.h>
#include <WS2tcpip.h>

#endif
