/*
 * Copyright (c) 2014, Oculus VR, Inc.
 * All rights reserved.
 *
 * This source code is licensed under the BSD-style license found in the
 * LICENSE file in the root directory of this source tree. An additional grant
 * of patent rights can be found in the PATENTS file in the same directory.
 */

#include "RakNetDefines.h"

#if defined(_WIN32)                                  \
    && !(defined(__GNUC__) || defined(__GCCXML__))   \
    && defined(_RAKNET_DLL) && !defined(_RAKNET_LIB)
#define RAK_DLL_EXPORT __declspec(dllexport)
#else
#define RAK_DLL_EXPORT
#endif

#define STATIC_FACTORY_DECLARATIONS(_x) \
    static _x * GetInstance();          \
    static void DestroyInstance(_x *i);

#define STATIC_FACTORY_DEFINITIONS(_x, _y)            \
    _x *                                              \
    _x::GetInstance() {                               \
        return RakNet::OP_NEW<_y>(_FILE_AND_LINE_);   \
    }                                                 \
                                                      \
    void                                              \
    _x::DestroyInstance(_x *i) {                      \
        RakNet::OP_DELETE((_y *) i, _FILE_AND_LINE_); \
    }
