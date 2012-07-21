/*
 * =====================================================================================
 *
 *       Filename:  constants.h
 *
 *    Description:  Just some quick constants because I'm lazy and terrible
 *
 *        Version:  1.0
 *        Created:  07/04/2012
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Yamamushi (Jon Rumion)
 *   Organization:  The ASCII Project
 *
 *	  License:  GPLv3
 *
 *	  Copyright 2012 Jonathan Rumion
 *
 *   This file is part of The ASCII Project.
 *
 *   The ASCII Project is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.
 *
 *   The ASCII Project is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with The ASCII Project.  If not, see <http://www.gnu.org/licenses/>.
 *
 *
 * =====================================================================================
 */

// the constant TCP_BUFSIZE_READ is the maximum size of the standard input
// buffer of TcpSocket
#define RSIZE TCP_BUFSIZE_READ

#define MaxDataSize 16

#define MAIN_WIDTH 80
#define MAIN_HEIGHT 45

#define MAP_WIDTH 80
#define MAP_HEIGHT 45

#define LIMIT_FPS 20

#define ROOM_MAX_SIZE 10
#define ROOM_MIN_SIZE 6
#define MAX_ROOMS 20
#define MAX_HALLS 100

#define FOV_ALGO 0
#define FOV_LIGHT_WALLS true
#define TORCH_RADIUS 10



enum colors {

        RANDOM,
        NONE,
        DARK_WALL,
        DARK_GROUND,
        LIGHT_WALL,
        LIGHT_GROUND,
        BLACK,
        BLUE,
        LIGHT_BLUE,
        YELLOW,
        GOLD,
	RED,
	WHITE,

};



enum entity_types {

	RESERVED,
	DEFAULT,
	PLAYER,
	MONSTER,

};


typedef struct render_t {
    wchar_t *symbol;
    float H;
    float S;
    float V;
    float HD;
    float SD;
    float VD;
    bool explored;
    bool occupied;
    bool visible;
};


struct SerializedPacket {
    int senderId;
    int sequenceNumber;
    char data[MaxDataSize];
} __attribute__((packed));




















