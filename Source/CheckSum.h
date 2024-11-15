/*
 * Copyright (c) 2014, Oculus VR, Inc.
 * All rights reserved.
 *
 * This source code is licensed under the BSD-style license found in the
 * LICENSE file in the root directory of this source tree. An additional grant
 * of patent rights can be found in the PATENTS file in the same directory.
 */

/*!
 * @file ChecSum.cpp
 * 
 * @brief [Internal] CheckSum implementation from http://www.flounder.com/checksum.htm
 */

#ifndef RAKNET_CHECKSUM_H
#define RAKNET_CHECKSUM_H

#include "RakMemoryOverride.h"

class CheckSum {

private:

    unsigned short r;
    unsigned short c1;
    unsigned short c2;
    unsigned int sum;

public:

    CheckSum();

    unsigned int Get();
    
    void Add(unsigned int   w);
    void Add(unsigned short w);
    void Add(unsigned char  b);
    void Add(unsigned char *b, unsigned int length);

    void Clear();

};

#endif /* RAKNET_CHECKSUM_H */
