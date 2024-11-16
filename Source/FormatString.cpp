/*
 * Copyright (c) 2014, Oculus VR, Inc.
 * All rights reserved.
 *
 * This source code is licensed under the BSD-style license found in the
 * LICENSE file in the root directory of this source tree. An additional grant
 * of patent rights can be found in the PATENTS file in the same directory.
 */
#include "FormatString.h"

#include <stdarg.h>
#include <stdio.h>
#include <string.h>

#include "LinuxStrings.h"

#define TEXT_BUFFER_COUNT 4
#define TEXT_BUFFER_SIZE  8096

char *
FormatString(const char *format, ...) {
    static int bufferIndex = 0;
    static char buffers[TEXT_BUFFER_COUNT][TEXT_BUFFER_SIZE];

    va_list ap;
    va_start(ap, format);
    _vsnprintf(buffers[bufferIndex], TEXT_BUFFER_SIZE, format, ap);
    va_end(ap);

    buffers[bufferIndex][TEXT_BUFFER_SIZE - 1] = '\0';

    char *buffer = buffers[bufferIndex];

    bufferIndex += 1;
    if (bufferIndex == 4) {
        bufferIndex = 0;
    }

    return buffer;
}

char *
FormatStringTS(char *output, const char *format, ...) {
    va_list ap;

    /* TODO: WTF does this use 512 while the other uses 8096??? */
    va_start(ap, format);
    _vsnprintf(output, 512, format, ap);
    va_end(ap);

    return output;
}
