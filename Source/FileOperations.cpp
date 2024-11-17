/*
 * Copyright (c) 2014, Oculus VR, Inc.
 * All rights reserved.
 *
 * This source code is licensed under the BSD-style license found in the
 * LICENSE file in the root directory of this source tree. An additional grant
 * of patent rights can be found in the PATENTS file in the same directory.
 */
#include "FileOperations.h"

#if RAKNET_SUPPORT_FileOperations == 1

#include <stdio.h>
#include <errno.h>
#include <string.h>

#include "RakMemoryOverride.h"
#include "_FindFirst.h"

#ifdef _WIN32 

#include <direct.h>
#include <io.h>

#define MAKE_DIR(_path) _mkdir((_path))

#else

#include <sys/stat.h>
#include <unistd.h>

#define MAKE_DIR(_path)  mkdir((_path), 0744)

#endif

#ifndef MAX_PATH
#define MAX_PATH 260
#endif

#ifdef _MSC_VER
#pragma warning(push)
#endif

/*
 * Microsoft has deprecated mkdir because they want us to use the Win32
 * API. I'm really happy that the Win32 API is really convenient, easy to
 * use, and not a total pain in the ass. Surely they wouldn't deprecate
 * it if that were the case.
 */
#ifdef _MSC_VER
#pragma warning( disable : 4996 )
#endif

bool
WriteFileWithDirectories(const char *path, char *data, unsigned dataLength) {
    if (!path || !path[0]) {
        return false;
    }

    char pathCopy[MAX_PATH];
    strcpy(pathCopy, path);

    /* ignore first "/" if there is one */
    if (pathCopy[0]) {
        size_t index = 1;
        while (pathCopy[index]) {
            if (pathCopy[index] != '/' && pathCopy[index] != '\\') {
                continue;
            }

            pathCopy[index] = '\0';

            int result = MAKE_DIR(pathCopy);
            if (result < 0 && errno != EEXIST && errno != EACCES) {
                return false;
            }

            pathCopy[index] = '/';
            index += 1;
        }
    }

    if (data) {
        FILE *file = fopen(path, "wb");
        if (!file) {
            return false;
        }
        fwrite(data, 1, dataLength, file);
        fclose(file);
    } else {
        int result = MAKE_DIR(pathCopy);
        if (result < 0 && errno != EEXIST) {
            return false;
        }
    }

    return true;
}

bool
IsSlash(unsigned char c) {
    return c == '/' || c == '\\';
}

void
AddSlash(char *input) {
    if (!input || !input[0]) {
        return;
    }

    int lastCharIndex = strlen(input) - 1;
    if (input[lastCharIndex] == '\\') {
        input[lastCharIndex] = '/' ;
    } else if (input[lastCharIndex] != '/') {
        input[lastCharIndex + 1] = '/';
        input[lastCharIndex + 2] = '\0';
    }
}

bool
DirectoryExists(const char *directory) {
    /*
     * TODO: 560 feels like an arbitrary choice here,
     *  does hthis correspond to something?
     */
    char baseDirWithStars[560];
    strcpy(baseDirWithStars, directory);
    AddSlash(baseDirWithStars);
    strcat(baseDirWithStars, "*.*");

    _finddata_t fileInfo;
    intptr_t dir = _findfirst(baseDirWithStars, &fileInfo );
    if (dir == -1) {
        return false;
    }

    _findclose(dir);
    return true;
}

void
QuoteIfSpaces(char *str) {
    bool hasSpace = false;
    for (unsigned i = 0; str[i]; i++) {
        if (str[i] == ' ') {
            hasSpace = true;
            break;
        }
    }

    if (hasSpace) {
        int len = strlen(str);
        memmove(str + 1, str, len);
        str[0] = '\"';
        str[len] = '\"';
        str[len + 1] = '\0';
    }
}

/* TODO: USING AN INT HERE IS A BUG */
unsigned int
GetFileLength(const char *path) {
    FILE *file = fopen(path, "rb");
    if (!file) {
        return 0;
    }

    fseek(file, 0, SEEK_END);
    unsigned int len = ftell(file);
    fclose(file);

    return len;
}

#ifdef _MSC_VER
#pragma warning(pop)
#endif

#endif /* RAKNET_SUPPORT_FileOperations */
