/*
 * =====================================================================================
 *
 *       Filename:  map.h
 *
 *    Description:  Our map drawing functions header (will be replaced)
 *
 *        Version:  1.0
 *        Created:  07/03/2012 07:50:52 AM
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


class Tile {
	private:

	public:

		int posX, posY;
		bool blocked;
		bool block_sight;
		bool is_wall;

		Tile(bool blked);
		void init_Tile(bool);
		bool is_sight_blocked();
		bool is_blocked();
};


class Rect {
	public:
		int x1, x2, y1, y2;
		Rect(int, int, int, int);
		void initRect(int, int, int, int);
};


class Room {
	private:

	public:
		Rect *dim;
		Room(int, int, int, int);
		void initRoom(int, int, int, int);
};	


class Hall {
	private:

	public:
		Hall(int, int, int);
		void initHall(int, int, int);
};





class Map {
	private:
		int x, y, z, i;
		TCODConsole *tgt;

	public:
		Room * rooms[MAX_ROOMS];
		Map(int, int);
		void initMap(int, int);
		void drawMap(TCODConsole *dest);
		void checkBounds(entity *target, Keyboard *buffer);
		void createRoom(int, int, int, int);
		void createHall(int, int, int);

};














