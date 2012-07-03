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
 * =====================================================================================
 */

class Tile {
	private:
		int posX, posY;
		bool blocked;
		bool block_sight;
		bool is_wall;

	public:
		Tile(bool blked);
		void init_Tile(bool);

};

