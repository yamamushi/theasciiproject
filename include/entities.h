/*
 * =====================================================================================
 *
 *       Filename:  entities.h
 *
 *    Description:  Our entities header file
 *
 *        Version:  1.0
 *        Created:  07/03/2012 03:42:54 AM
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


class EntityMap;


class Entity {
	private:

		int X, Y;
		char *symbol;
		Map *world;

		bool initialized;

		EntityMap *entMap;

	public:


		void init_entity( char* symbol );
		bool move(Map *destination, int dx, int dy);
		int posX();
		int posY();
		int TypeID, subTypeID;
		bool fov[MAP_WIDTH][MAP_HEIGHT];
		float H, S, V;
		int R, G, B;

		void init_in_world(Map *destination);


		char *getSymbol();

		bool isInitialized();



		void move_self(int dx, int dy);

		void setEntityMap(EntityMap *map);



};



class EntityMap {

	private:

		int width, height;
                vector<Entity *> pos[MAP_WIDTH][MAP_HEIGHT];

		int colorTable[MAP_WIDTH][MAP_HEIGHT];
		char *symbolTable[MAP_WIDTH][MAP_HEIGHT];

		Entity *current;

	public:

		Entity *player;

		EntityMap(int x, int y);
		void initEntityMap(int x, int y);
		void refreshGraphicsMap();

		void addToMap(Entity *entity);
		void createEntity(int type);


		void initAllEnts(Map *destination);
		void refreshEntityMap();

		bool checkOccupied(int x, int y);
		Entity * outputLastEntity(int x, int y);

		int checkColor(int x, int y);

		void updateColorMap();



};





// These entities are for testing purposes only
// and will be moved in the coming days.


class Monster : public Entity {

	public:

		Monster();

};


class Player : public Entity {

	public:
		Player();

};


class Goblin : public Entity {

	public:
		Goblin();

};
