/*
 * =====================================================================================
 *
 *       Filename:  RenderMap.h
 *
 *    Description:  This object stores the Symbol and Color information
 *              for use in our Graphics Rendering library.
 *
 *        Version:  1.0
 *        Created:  07/19/2012
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

// I apologize ahead of time for the code indentation here, Netbeans
// is not playing nice right now.

struct render_t {
    wchar_t *symbol;
    float H;
    float S;
    float V;
};


class RenderMap {

private:

    render_t * Rmap[MAP_WIDTH][MAP_HEIGHT];
    Entity *scan;


public:

    RenderMap(TileMap *tiles, EntityMap *entities);
    void initRenderMap(TileMap *tiles, EntityMap *entities);

    wchar_t *getSymbol(int x, int y);



};