/*
 * Copyright (c) 2014, Oculus VR, Inc.
 * All rights reserved.
 *
 * This source code is licensed under the BSD-style license found in the
 * LICENSE file in the root directory of this source tree. An additional grant
 * of patent rights can be found in the PATENTS file in the same directory.
 */
#ifndef RAKNET_GET_TIME_H
#define RAKNET_GET_TIME_H

#include "Export.h"
#include "RakNetTime.h"

namespace RakNet {

    /*!
     * @brief
     * Same as, but not an alias for, #GetTimeMS.
     * 
     * @details
     * This holds the time in either a 32-bit or 64-bit variables,
     * depending on #GET_TIME_64BIT.
     */
    RAK_DLL_EXPORT RakNet::Time GetTime();

    /*!
     * @brief
     * Return the time in milliseconds as a 32-bit value.
     * 
     * @note
     * The maximum delta between returned calls is one second.
     * However, RakNet calls this constantly anyway.
     * See #NormalizeTime() in `GetTime.cpp` for an explanation.
     */
    RAK_DLL_EXPORT RakNet::TimeMS GetTimeMS();

    /*!
     * @brief
     * Returns the time in microseconds as a 64-bit value.
     */
    RAK_DLL_EXPORT RakNet::TimeUS GetTimeUS();

    /*!
     * @brief
     * Returns if timestamp `a` is greater than timestamp `b`, accounting
     * for timestamps wrapping around to zero after an overflow.
     */
    RAK_DLL_EXPORT bool GreaterThan(RakNet::Time a, RakNet::Time b);

    /*!
     * @brief
     * Returns if timestamp `a` is less than timestamp `b`, accounting
     * for timestamps wrapping around to zero after an overflow.
     */
    RAK_DLL_EXPORT bool LessThan(RakNet::Time a, RakNet::Time b);

}

#endif /* RAKNET_GET_TIME_H */
