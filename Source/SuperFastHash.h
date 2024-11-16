/*
 * Copyright (c) 2014, Oculus VR, Inc.
 * All rights reserved.
 *
 * This source code is licensed under the BSD-style license found in the
 * LICENSE file in the root directory of this source tree. An additional grant
 * of patent rights can be found in the PATENTS file in the same directory.
 */
#ifndef RAKNET_SUPER_FAST_HASH_H
#define RAKNET_SUPER_FAST_HASH_H

#include <stdio.h>

#include "NativeTypes.h"

/*
 * Taken from: http://www.azillionmonkeys.com/qed/hash.html
 * The author of the main code is Paul Hsieh.
 * Some convenience functions have been added.
 * 
 * Also note http://burtleburtle.net/bob/hash/doobs.html, which
 * shows that this is 20% faster than the one on that page but has
 * more collisions.
 */

uint32_t SuperFastHash(const char *data, int length);
uint32_t SuperFastHashIncremental(const char *data, int length, unsigned int lastHash);
uint32_t SuperFastHashFile(const char *filename);
uint32_t SuperFastHashFilePtr(FILE *fp);

#endif /* RAKNET_SUPER_FAST_HASH_H */
