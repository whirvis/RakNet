/*
 * Copyright (c) 2014, Oculus VR, Inc.
 * All rights reserved.
 *
 * This source code is licensed under the BSD-style license found in the
 * LICENSE file in the root directory of this source tree. An additional grant
 * of patent rights can be found in the PATENTS file in the same directory.
 */
#ifndef RAKNET_GCC_WIN_STRINGS
#define RAKNET_GCC_WIN_STRINGS

#if !defined(_WIN32) && (defined(__GNUC__) || defined(__GCCXML__))

#ifndef _stricmp
int _stricmp(const char *s1, const char *s2);
#endif

int _strnicmp(const char *s1, const char *s2, size_t n);

#ifndef _vsnprintf
#define _vsnprintf vsnprintf
#endif

#ifndef __APPLE__
char * _strlwr(char *str); /* this won't compile on OSX for some reason */
#endif

#endif

#endif /* RAKNET_GCC_WIN_STRINGS */
