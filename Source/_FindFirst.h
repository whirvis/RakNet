/*
 * Copyright (c) 2014, Oculus VR, Inc.
 * All rights reserved.
 *
 * This source code is licensed under the BSD-style license found in the
 * LICENSE file in the root directory of this source tree. An additional grant
 * of patent rights can be found in the PATENTS file in the same directory.
 */
#ifndef RAKNET_GCC_FINDFIRST_H
#define RAKNET_GCC_FINDFIRST_H

/*
 * Original code written by "the_viking", with fixes by Rômulo Fernandes.
 * This should emulate the finddata structure found in the Win32 API.
 */

#if !defined(__WIN32) && (defined(__GNUC__) || defined(__GCCXML__))

#include <dirent.h>

#include "RakString.h"

#define _A_NORMAL 0x00 /* normal file                     */
#define _A_RDONLY 0x01 /* read only file                  */
#define _A_HIDDEN 0x02 /* hidden file                     */
#define _A_SYSTEM 0x04 /* system file                     */
#define _A_VOLID  0x08 /* volume ID                       */
#define _A_SUBDIR 0x10 /* subdirectory                    */
#define _A_ARCH   0x20 /* file changed since last archive */

#define FA_NORMAL _A_NORMAL
#define FA_RDONLY _A_RDONLY
#define FA_HIDDEN _A_HIDDEN
#define FA_SYSTEM _A_SYSTEM
#define FA_LABEL  _A_VOLID
#define FA_DIREC  _A_SUBDIR
#define FA_ARCH   _A_ARCH

#define _FIND_FIRST_STRING_BUFFER_SIZE 512

typedef struct _finddata_t {
    char          name[_FIND_FIRST_STRING_BUFFER_SIZE];
    int           attrib;
    unsigned long size;
} _finddata;

typedef struct _findinfo_t {
    DIR               *openedDir;
    RakNet::RakString  filter;
    RakNet::RakString  dirName;
} _findinfo;

long _findfirst(const char *name, _finddata_t *f);
int _findnext(long h, _finddata_t *f);
int _findclose(long h);

#endif

#endif /* RAKNET_GCC_FIND_FIRST_H */
