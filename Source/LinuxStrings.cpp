/*
 * Copyright (c) 2014, Oculus VR, Inc.
 * All rights reserved.
 *
 * This source code is licensed under the BSD-style license found in the
 * LICENSE file in the root directory of this source tree. An additional grant
 * of patent rights can be found in the PATENTS file in the same directory.
 */
#include "LinuxStrings.h"

#if !defined(_WIN32) && (defined(__GNUC__) || defined(__GCCXML__))

#include <string.h>

#ifndef _stricmp
int
_stricmp(const char* s1, const char* s2) {
    return strcasecmp(s1,s2);
}
#endif

int
_strnicmp(const char* s1, const char* s2, size_t n) {
    return strncasecmp(s1,s2,n);
}

#ifndef __APPLE__
char *
_strlwr(char * str ) {
    if (!str) {
        return NULL;
    }

    for (int i = 0; str[i]; i++) {
	if (str[i] >= 'A' && str[i] <= 'Z') {
	    str[i] += 'a' - 'A';
        }
    }

    return str;
}
#endif

#endif
