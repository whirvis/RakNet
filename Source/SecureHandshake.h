/*
 * Copyright (c) 2014, Oculus VR, Inc.
 * All rights reserved.
 *
 * This source code is licensed under the BSD-style license found in the
 * LICENSE file in the root directory of this source tree. An additional grant
 * of patent rights can be found in the PATENTS file in the same directory.
 */
#ifndef RAKNET_SECURE_HANDSHAKE_H
#define RAKNET_SECURE_HANDSHAKE_H

#include "NativeFeatureIncludes.h"

#if LIBCAT_SECURITY == 1

/* if building a DLL, tweak the CAT_EXPORT macro meaning */
#if !defined(_RAKNET_LIB) && defined(_RAKNET_DLL)
#define CAT_BUILD_DLL
#else
#define CAT_NEUTER_EXPORT
#endif

/* include DependentExtensions in your path for this */
#include "cat/AllTunnel.hpp"

#endif

#endif /* RAKNET_SECURE_HANDSHAKE_H */
