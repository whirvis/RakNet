/*
 * Copyright (c) 2014, Oculus VR, Inc.
 * All rights reserved.
 *
 * This source code is licensed under the BSD-style license found in the
 * LICENSE file in the root directory of this source tree. An additional grant
 * of patent rights can be found in the PATENTS file in the same directory.
 */
#ifndef RAKNET_FILE_OPERATIONS_H
#define RAKNET_FILE_OPERATIONS_H

#include "NativeFeatureIncludes.h"

#if RAKNET_SUPPORT_FileOperations == 1

#include "Export.h"

RAK_DLL_EXPORT bool WriteFileWithDirectories(const char *path, char *data, unsigned dataLength);

RAK_DLL_EXPORT bool IsSlash(unsigned char c);

RAK_DLL_EXPORT void AddSlash(char *input);

RAK_DLL_EXPORT void QuoteIfSpaces(char *str);

RAK_DLL_EXPORT bool DirectoryExists(const char *directory);

RAK_DLL_EXPORT unsigned int GetFileLength(const char *path);

#endif /* RAKNET_SUPPORT_FileOperations */

#endif /* RAKNET_FILE_OPERATIONS_H */
