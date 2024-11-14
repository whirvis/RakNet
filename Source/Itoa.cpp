/*
 * Copyright (c) 2014, Oculus VR, Inc.
 * All rights reserved.
 *
 * This source code is licensed under the BSD-style license found in the
 * LICENSE file in the root directory of this source tree. An additional grant
 * of patent rights can be found in the PATENTS file in the same directory.
 */
#include "Itoa.h"

static const char *NUMERIC_CHARS = "0123456789abcdef";

/*
 * Fast implementation of `itoa`, taken from Manchester University
 * for Linux; since it seems Linux doesn't support this function.
 * It has been modified so as not to have any dependences on the C
 * standard library.
 */
char *
Itoa(int value, char *result, int base) {
    /* terminate if base is unsupported */
    if (base < 2 || base > 16) {
        *result = '\0';
        return result;
    }

    char *out = result;
    int quotient = value;

    int charIndex;
    do {
        charIndex = quotient % base;
        if (charIndex < 0) {
            charIndex = -charIndex;
        }
        *out++ = NUMERIC_CHARS[charIndex];
        quotient /= base;
    } while (quotient);

    /* only apply negative sign for decimal */
    if (value < 0 && base == 10) {
        *out++ = '-';
    }
    
    /* terminate the string */
    *out = '\0';
    
    /* lastly reverse the string */
    char *start = result;
    out--; /* don't reverse the terminator */
    char temp;
    while (start < out) {
        temp = *start;
        *start++ = *out;
        *out-- = temp;
    }

    return result;
}
