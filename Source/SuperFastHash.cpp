/*
 * Copyright (c) 2014, Oculus VR, Inc.
 * All rights reserved.
 *
 * This source code is licensed under the BSD-style license found in the
 * LICENSE file in the root directory of this source tree. An additional grant
 * of patent rights can be found in the PATENTS file in the same directory.
 */
#include "SuperFastHash.h"

#include <stdlib.h>

#include "NativeTypes.h"

#define INCREMENTAL_READ_BLOCK 65536

#if defined(_MSC_VER)                               \
        || (defined(__GNUC__) && defined(__i386__)) \
        || defined(__BORLANDC__)                    \
        || defined(__TURBOC__)                      \
        || defined(__WATCOMC__)
    #define get16bits(_i) (*((const uint16_t *) (_i)))
#else
    #define get16bits(_i)                                   \
        ( (((uint32_t) (((const uint8_t *) (_i))[1])) << 8) \
        +  ((uint32_t) (((const uint8_t *) (_i))[0]))       )
#endif

uint32_t
SuperFastHash(const char *data, int length) {
    unsigned int lastHash = length;

    /*
     * This implementation is necessary to ensure the produced hash is
     * identicial to the one produced by SuperFastHashIncremental.
     */

    int remaining = length;
    int offset = 0;
    while (remaining >= INCREMENTAL_READ_BLOCK) {
        lastHash = SuperFastHashIncremental(data + offset,
            INCREMENTAL_READ_BLOCK, lastHash);
        remaining -= INCREMENTAL_READ_BLOCK;
        offset += INCREMENTAL_READ_BLOCK;
    }

    if (remaining > 0) {
        lastHash = SuperFastHashIncremental(data + offset,
            remaining, lastHash);
    }

    return lastHash;
}

uint32_t
SuperFastHashIncremental(const char *data, int length, unsigned int lastHash) {
    if (!data || length <= 0) {
        return 0;
    }

    uint32_t hash = lastHash;
    int remainder = length & 3;
    length >>= 2;

    uint32_t temp;
    while (length > 0) {
        hash += get16bits(data);
        temp = (get16bits(data + 2) << 11) ^ hash;
        hash = (hash << 16) ^ temp;
        hash += hash >> 11;
        
        data  += 2 * sizeof(uint16_t);
        length -= 1;
    }

    switch (remainder) {
    case 3:
        hash += get16bits(data);
        hash ^= hash << 16;
        hash ^= data[sizeof(uint16_t)] << 18;
        hash += hash >> 11;
        break;
    case 2:
        hash += get16bits(data);
        hash ^= hash << 11;
        hash += hash >> 17;
        break;
    case 1:
        hash += *data;
        hash ^= hash << 10;
        hash += hash >> 1;
        break;
    }

    /* force "avalanching" of final 127 bits */
    hash ^= hash << 3;
    hash += hash >> 5;
    hash ^= hash << 4;
    hash += hash >> 17;
    hash ^= hash << 25;
    hash += hash >> 6;

    return hash;
}

uint32_t
SuperFastHashFile(const char *filename) {
    FILE *file = fopen(filename, "rb");
    if (!file) {
        return 0;
    }

    uint32_t hash = SuperFastHashFilePtr(file);
    fclose(file);
    return hash;
}

uint32_t
SuperFastHashFilePtr(FILE *fp) {
    /*
     * Use the heap instead of the stack here, this
     * much data is admittedly quite a lot to place
     * on the stack all at once.
     */
    char *readBlock = new char[INCREMENTAL_READ_BLOCK];

    /*
     * TODO: USING int HERE IS A BUG BUT I CAN'T CHANGE IT
     *  OTHERWISE THIS FUNCTION WILL GIVE DIFFERENT OUTPUTS
     *  FROM THE ORIGINAL VERSIONFOR THE SAME INTPUTS.
     */
    fseek(fp, 0, SEEK_END);
    int length = ftell(fp); /* <- BAD :( */
    fseek(fp, 0, SEEK_SET);

    unsigned int lastHash = length;
    long remaining = length;

    while (remaining >= sizeof(readBlock)) {
        fread(readBlock, sizeof(readBlock), 1, fp);
        lastHash = SuperFastHashIncremental(readBlock,
            sizeof(readBlock), lastHash);
        remaining -= sizeof(readBlock);
    }

    if (remaining > 0) {
        fread(readBlock, remaining, 1, fp);
        lastHash = SuperFastHashIncremental(readBlock,
            remaining, lastHash);
    }

    delete[] readBlock;
    return lastHash;
}
