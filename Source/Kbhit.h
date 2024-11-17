/*
 * Copyright (c) 2014, Oculus VR, Inc.
 * All rights reserved.
 *
 * This source code is licensed under the BSD-style license found in the
 * LICENSE file in the root directory of this source tree. An additional grant
 * of patent rights can be found in the PATENTS file in the same directory.
 */
#ifndef RAKNET_KBHIT_H
#define RAKNET_KBHIT_H

/*
 * Chris Giese <geezer@execpc.com>
 * http://my.execpc.com/~geezer
 * This code is in the public domain.
 */

#if defined(_WIN32)

#include <conio.h>

#else

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/time.h>
#include <termios.h>
#include <unistd.h>

static struct termios old_kbd_mode;

static void
cooked(void) {
    tcsetattr(0, TCSANOW, &old_kbd_mode);
}

static void
raw(void) {
    static bool initialized = false;

    if(initialized) {
	return;
    }

    tcgetattr(0, &old_kbd_mode);
    struct termios new_kbd_mode;
    memcpy(&new_kbd_mode, &old_kbd_mode, sizeof(old_kbd_mode));

    /* put stdin into raw, unbuffered mode */
    new_kbd_mode.c_lflag &= ~(ICANON /* | ECHO */ );
    new_kbd_mode.c_cc[VTIME] = 0;
    new_kbd_mode.c_cc[VMIN] = 1;
    tcsetattr(0, TCSANOW, &new_kbd_mode);

    /* when we exit, go back to normal, "cooked" mode */
    atexit(cooked);

    initialized = true;
}

static int 
kbhit(void) {
    static struct timeval timeout = { 0 };

    raw();

    /* check stdin for activity */
    fd_set read_handles;
    FD_ZERO(&read_handles);
    FD_SET(stdin, &read_handles);

    int status = select(1, &read_handles, NULL, NULL, &timeout);
    if(status < 0) {
	printf("select() failed in kbhit()\n");
	exit(1);
    }

    return status;
}

static int
getch(void) {
    raw();

    unsigned char temp;
    if(read(stdin, &temp, 1) != 1){
	return 0;
    }

    return temp;
}

#endif

#endif /* RAKNET_KBHIT_H */
