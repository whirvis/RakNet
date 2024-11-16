/*
 * Copyright (c) 2014, Oculus VR, Inc.
 * All rights reserved.
 *
 * This source code is licensed under the BSD-style license found in the
 * LICENSE file in the root directory of this source tree. An additional grant
 * of patent rights can be found in the PATENTS file in the same directory.
 */
#ifndef RAKNET_VERSION_H
#define RAKNET_VERSION_H

#define RAKNET_VERSION            "4.081"
#define RAKNET_VERSION_NUMBER      4.081
#define RAKNET_VERSION_NUMBER_INT  4081

#define RAKNET_DATE "5/28/2014"

/*
 * The protocol version being on 6 here is odd. Minecraft is on
 * version 10 at time of writing. Are they updating RakNet behind
 * the scenes?
 * 
 * I don't think so, because JRakNet (which I haven't touched for
 * years) seems to still be compatible with it, the only required
 * change being the protocol version in the RakNet class.
 * 
 * My assumption is that it's common to change the RakNet version
 * so incompatible protocols for *games*, not RakNet, are enforced
 * by RakNet automatically rather than the game needing to do any
 * extra work. Even then, I could swear the Minecraft protocol has
 * packets sent during player connection exactly for that purpose.
 */

/*!
 * @brief
 * The current protocol version of RakNet.
 *
 * @details
 * When this value changes, it indicates this version of RakNet
 * cannot communicate with an older version. When attempted, an
 * `ID_INCOMPATIBLE_PROTOCOL_VERSION` will be returned.
 */
#define RAKNET_PROTOCOL_VERSION 6

#endif /* RAKNET_VERSION_H */
