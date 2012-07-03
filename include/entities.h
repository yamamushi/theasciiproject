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
 * =====================================================================================
 */


class entity {
	private:
		int posX, posY;
		char* symbol;
		TCODColor fore;
		
		entity() { }

	public:
		entity(int posX, int posY, char* symbol, TCODColor fore);	
		void init_entity(int, int, char*, TCODColor);
		void move(int, int);
		void draw(TCODConsole *dest);
};




