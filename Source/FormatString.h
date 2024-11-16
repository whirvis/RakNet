/*
 * Copyright (c) 2014, Oculus VR, Inc.
 * All rights reserved.
 *
 * This source code is licensed under the BSD-style license found in the
 * LICENSE file in the root directory of this source tree. An additional grant
 * of patent rights can be found in the PATENTS file in the same directory.
 */
#ifndef RAKNET_FORMAT_STRING_H
#define RAKNET_FORMAT_STRING_H

#include "Export.h"

#ifdef __cplusplus
extern "C" {
#endif

char * FormatString(const char *format, ...);

char * FormatStringTS(char *output, const char *format, ...);

#ifdef __cplusplus
}
#endif

#endif /* RAKNET_FORMAT_STRING_H */
