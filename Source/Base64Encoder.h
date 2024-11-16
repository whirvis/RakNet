/*
 * Copyright (c) 2014, Oculus VR, Inc.
 * All rights reserved.
 *
 * This source code is licensed under the BSD-style license found in the
 * LICENSE file in the root directory of this source tree. An additional grant
 * of patent rights can be found in the PATENTS file in the same directory.
 */
#ifndef RAKNET_BASE_64_ENCODER_H
#define RAKNET_BASE_64_ENCODER_H

#include "Export.h"

#ifdef __cplusplus
extern "C" {
#endif

/*!
 * @brief
 * Returns the map used for Base64 encoding.
 */
const char *Base64Map();

/*!
 * @brief
 * Converts a byte array to a Base64 encoded string.
 * 
 * @warn The `output` buffer must have a size of at least
 *       `(inputLength * 2) + 6`.
 * 
 * @param[in] input       The byte array to encode.
 * @param[in] inputLength The size of `input` in bytes.
 * @param[in] output      Where to write the string.
 * 
 * @return How many bytes were written to `output`.
 */
int Base64Encoding(const unsigned char *input, int inputLength, char *output);

#ifdef __cplusplus
}
#endif

/*
 * The function below is overloaded, so it must not go inside the above
 * extern "C" block (functions with C linkage cannot be overloaded).
 */

/*!
 * @brief
 * Converts a byte array to a Base64 encoded string.
 * 
 * This version of the method allocates the necessary memory to store the
 * encoded string. The caller is responsible for freeing this string once
 * once they are through with it.
 * 
 * @param[in]  input       The byte array to encode.
 * @param[in]  inputLength The size of `input` in bytes.
 * @param[out] output      Where to write the pointer to the string.
 * 
 * @return How many bytes were written to `output`.
 */
int Base64Encoding(const unsigned char *input, int inputLength, char **output);

#endif /* RAKNET_BASE_64_ENCODER_H */
