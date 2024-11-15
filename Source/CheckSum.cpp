/*
 * Copyright (c) 2014, Oculus VR, Inc.
 * All rights reserved.
 *
 * This source code is licensed under the BSD-style license found in the
 * LICENSE file in the root directory of this source tree. An additional grant
 * of patent rights can be found in the PATENTS file in the same directory.
 */
#include "CheckSum.h"

inline
CheckSum::CheckSum() {
    this->Clear();
}

inline unsigned int
CheckSum::Get() {
    return this->sum;
}

void
CheckSum::Add(unsigned int value) {
    union {
        unsigned int value;
        unsigned char bytes[4];
    } data = { 0 };

    data.value = value;
    for (unsigned int i = 0; i < sizeof(data.bytes); i++) {
        this->Add(data.bytes[i]);
    }
}

void
CheckSum::Add(unsigned short value) {
    union {
        unsigned short value;
        unsigned char bytes[2];
    } data = { 0 };

    data.value = value;
    for (unsigned int i = 0; i < sizeof(data.bytes); i++) {
        this->Add (data.bytes[i]);
    }
}

void
CheckSum::Add(unsigned char value) {
    unsigned char cipher = (unsigned char) (value ^ (r >> 8));
    this->r = (cipher + r) * c1 + c2;
    this->sum += cipher;
}

void
CheckSum::Add (unsigned char *b, unsigned int length) {
    for (unsigned int i = 0; i < length; i++) {
        this->Add(b[i]);
    }
}

inline void
CheckSum::Clear() {
   this->r = 55665;
   this->c1 = 52845;
   this->c2 = 22719;
   this->sum = 0;
}
