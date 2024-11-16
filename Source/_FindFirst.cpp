/*
 * Copyright (c) 2014, Oculus VR, Inc.
 * All rights reserved.
 *
 * This source code is licensed under the BSD-style license found in the
 * LICENSE file in the root directory of this source tree. An additional grant
 * of patent rights can be found in the PATENTS file in the same directory.
 */
#include "_FindFirst.h"

/*
 * Original code written by "the_viking", with fixes by Rômulo Fernandes.
 * This should emulate the finddata structure found in the Win32 API.
 */

#if !defined(__WIN32) && (defined(__GNUC__) || defined(__GCCXML__))

#include <dirent.h>
#include <fnmatch.h>
#include <sys/stat.h>

#include "DS_List.h"
#include "RakAssert.h"
#include "RakMemoryOverride.h"
#include "RakString.h"

static DataStructures::List<_findinfo_t *> fileInfo;

long
_findfirst(const char *name, _finddata_t *f) {
    RakNet::RakString rakName = name;
    RakNet::RakString rakFilter;

    /*
     * This is Linux only, so don't bother with backslashes.
     *
     * If a "/" character is found, a filter pattern only was given
     * and the current directory should be searched. If not, strip
     * the filter pattern from the directory name while leaving the
     * trailing "/" intact.
     */
    const char *lastSep = strrchr(name, '/');
    if(!lastSep) {
        rakFilter = rakName;
        rakName = ".";
    } else {
        rakFilter = lastSep + 1;
        unsigned sepIndex = lastSep - name;
        rakName.Erase(sepIndex + 1, rakName.GetLength() - sepIndex - 1);
    }

    DIR *dir = opendir(rakName);
    if(!dir) {
        return -1;
    }

    _findinfo_t* fi = RakNet::OP_NEW<_findinfo_t>(_FILE_AND_LINE_);
    fi->filter    = rakFilter;
    fi->dirName   = rakName; /* this is needed for stat() later */
    fi->openedDir = dir;
    fileInfo.Insert(fi, _FILE_AND_LINE_);

    /*
     * Retrieve the first file.
     * We cannot rely on the first item being "."
     */
    long ret = fileInfo.Size() - 1;
    if (_findnext(ret, f) == -1) {
        return -1;
    }

    return ret;
}

int
_findnext(long h, _finddata_t *f) {
    RakAssert(h >= 0 && h < (long) fileInfo.Size());
    if (h < 0 || h >= (long) fileInfo.Size()) {
        return -1;
    }

    /*
     * TODO: Not a fan of this while(true) here, maybe it could be
     *  replaced with a proper condition rather than relying purely
     *  on a return or break statement?
     */
    _findinfo_t* fi = fileInfo[h];
    while(true) {
        dirent *entry = readdir(fi->openedDir);
        if(!entry) {
            return -1;
        }

        /* only report stuff matching our filter */
        if (fnmatch(fi->filter, entry->d_name, FNM_PATHNAME) != 0) {
            continue;
        }

        /*
         * To reliably determine the entry's type, we must use stat().
         * We cannot rely on entry->d_type, as it may be unavailable!
         */
        struct stat filestat;
        RakNet::RakString fullPath = fi->dirName + entry->d_name;             
        if (stat(fullPath, &filestat) != 0) {
            RAKNET_DEBUG_PRINTF("Failed to stat() \"%s\"\n",
                fullPath.C_String());
            continue;
        }

        if (S_ISREG(filestat.st_mode)) {
            f->attrib = _A_NORMAL;
        } else if (S_ISDIR(filestat.st_mode)) {
            f->attrib = _A_SUBDIR;                    
        } else {
            /*
             * We are only interested in files and directories,
             * linkes are currently not supported.
             */
            continue; 
        }

        f->size = filestat.st_size;
        strncpy(f->name, entry->d_name, _FIND_FIRST_STRING_BUFFER_SIZE);
        return 0;
    }

    return -1;
}

int
_findclose(long h) {
    if (h == -1) {
        return 0;
    }

    RakAssert(h >= 0 && h < (long) fileInfo.Size());
    if (h < 0 || h >= (long) fileInfo.Size()) {
        return -1;
    }

    _findinfo_t* fi = fileInfo[h];
    closedir(fi->openedDir);
    fileInfo.RemoveAtIndex(h);
    RakNet::OP_DELETE(fi, _FILE_AND_LINE_);

    return 0;   
}

#endif
