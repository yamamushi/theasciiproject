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
		bool visible;
		bool explored;
		bool occupied;

		Tile(bool blked=true);
		void init_Tile(bool);
		bool is_sight_blocked();
		bool is_blocked();
		bool is_visible();
		bool is_explored();
		friend class Map;
};


class Wall : public Tile {

	private:


	public:


};


class Floor : public Tile {
	private:

	public:
		Floor(bool blked=false);


};




class Rect {
	private:

	public:
		int x1, y1, x2, y2, cX, cY;
		Rect(int, int, int, int);
		void initRect(int, int, int, int);
};


class Room {
	private:

	public:
		int cX, cY;
		int x1, x2, y1, y2;
		Room(int, int, int, int);
		void initRoom(int, int, int, int);
		bool doesBorder(Room *other);
		bool doesContainPoint(int, int);
		bool doesIntersect(Room *other);

		friend class Map;

};	


class Hall {
	private:

	public:
		int x1, x2, y, dir;
		Hall(int, int, int, int);
		void initHall(int, int, int, int);

};





class Map {
	private:
		int x, y, z, i;
		int wid, hig;

	public:

		Room *rooms[MAX_ROOMS];
		int numRooms;
		Hall *halls[MAX_HALLS];
		int numHalls;

		Tile * virtMap[MAP_WIDTH][MAP_HEIGHT];	


		Map(int, int);
		void initMap(int, int);
		
		
		void clearMap();
		void refreshMap();
		bool checkBounds(int, int);
		
		void createRoom(int, int, int, int);
		void drawRoom(int i);
		void drawAllRooms();

		void createHall(int, int, int, int);
		void drawHall(int i);
		void drawAllHalls();

		void importRoom(Room *source);
		void importAllRooms(Map *source);
		void clearRooms();
		void clearRoom(int x);

		void importHall(Hall *source);
		void importAllHalls(Map *source);
		void clearHalls();
		void clearHall(int x);

		void copyVirtMap(Map *source);
		void importMap(Map *source);



};


