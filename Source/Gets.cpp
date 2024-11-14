/*
 * Copyright (c) 2014, Oculus VR, Inc.
 * All rights reserved.
 *
 * This source code is licensed under the BSD-style license found in the
 * LICENSE file in the root directory of this source tree. An additional grant
 * of patent rights can be found in the PATENTS file in the same directory.
 */
#include "Gets.h"

#include <cstdio>
#include <cstring>

char *
Gets (char *str, int num) {
    std::fgets(str, num, stdin);
    
    char c = str[0];
    if (c == '\n' || c == '\r') {
        str[0] = '\0';
    }

    size_t len = std::strlen(str);

    if (len > 0) {
        char d = str[len - 1];
        if((d == '\n' || d == '\r')) {
            str[len - 1] = '\0';
        }
    }

    if (len > 1) {
        char d = str[len - 2];
        if((d == '\n' || d == '\r')) {
            str[len - 2] = '\0';
        }
    }

    return str;
}
