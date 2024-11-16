/*
 * Copyright (c) 2014, Oculus VR, Inc.
 * All rights reserved.
 *
 * This source code is licensed under the BSD-style license found in the
 * LICENSE file in the root directory of this source tree. An additional grant
 * of patent rights can be found in the PATENTS file in the same directory.
 */
#include "Base64Encoder.h"

#include "RakMemoryOverride.h"

static const char *base64Map =
    "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

const char *
Base64Map() {
    return base64Map;
}

int
Base64Encoding(const unsigned char *input, int inputLength, char *output) {
    int offset = 0;
    int charCount = 0;

    int i = 0;
    int tripletCount = inputLength / 3;
    while (i < tripletCount) {
        /* Royal Dutch Airlines mentioned ?!?!?! */
        unsigned char k = input[i * 3 + 0];
        unsigned char l = input[i * 3 + 1];
        unsigned char m = input[i * 3 + 2];

        output[offset++] = base64Map[k >> 2];
        if ((++charCount % 76) == 0) {
            output[offset++] = '\r';
            output[offset++] = '\n';
            charCount = 0;
        }

        output[offset++] = base64Map[((k << 4) | (l >> 4)) & 63];
        if ((++charCount % 76) == 0) {
            output[offset++] = '\r';
            output[offset++] = '\n';
            charCount = 0;
        }

        output[offset++] = base64Map[((l << 2) | (m >> 6)) & 63];
        if ((++charCount % 76) == 0) {
            output[offset++] = '\r';
            output[offset++] = '\n';
            charCount = 0;
        }

        output[offset++] = base64Map[m & 63];
        if ((++charCount % 76) == 0) {
            output[offset++] = '\r';
            output[offset++] = '\n';
            charCount = 0;
        }

        i += 1;
    }

    if (inputLength % 3 == 1) {
        unsigned char k = input[i * 3 + 0];
        unsigned char l = input[i * 3 + 1];

        output[offset++]=base64Map[k >> 2];
        if ((++charCount % 76) == 0) {
            output[offset++] = '\r';
            output[offset++] = '\n';
            charCount = 0;
        }

        output[offset++]=base64Map[((k << 4) | (l >> 4)) & 63];
        if ((++charCount % 76) == 0) {
            output[offset++] = '\r';
            output[offset++] = '\n';
            charCount = 0;
        }

        output[offset++] = '=';
        output[offset++] = '=';
    } else if (inputLength % 3 == 2) {
        unsigned char k = input[i * 3 + 0];
        unsigned char l = input[i * 3 + 1];

        output[offset++] = base64Map[k >> 2];
        if ((++charCount % 76) == 0) {
            output[offset++] = '\r';
            output[offset++] = '\n';
            charCount = 0;
        }

        output[offset++] = base64Map[((k << 4) | (l >> 4)) & 63];
        if ((++charCount % 76) == 0) {
            output[offset++] = '\r';
            output[offset++] = '\n';
            charCount = 0;
        }

        output[offset++] = base64Map[(l << 2) & 63];
        if ((++charCount % 76) == 0) {
            output[offset++] = '\r';
            output[offset++] = '\n';
            charCount = 0;
        }

        output[offset++] = '=';
    }

    output[offset++] = '\r';
    output[offset++] = '\n';
    output[offset] = '\0';

    return offset;
}

int
Base64Encoding(const unsigned char *input, int inputLength, char **output) {
    /*
     * TODO: This is bad, this doesn't check if the allocation was
     *  successful before attempting to write to it. Does rakMalloc_Ex
     *  terminate the program if it fails to allocate? If so, then
     *  this isn't really an issue.
     */
    *output = (char *) rakMalloc_Ex(inputLength * 2 + 6, _FILE_AND_LINE_);
    return Base64Encoding(input, inputLength, *output);
}
