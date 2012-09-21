/*
 * =====================================================================================
 *
 *       Filename:  Serialization.h
 *
 *    Description:  This object defines the behavior of our "Entities", ie
 *                  The necessary functions for an entity to exist on the "Map"
 *
 *        Version:  1.0
 *        Created:  07/03/2012 03:41:29 AM
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


#pragma once
#include "tpl.h"
#include "constants.h"

class ClientMap;
class GraphicsTCOD;

class ClientMapPacker {

private:

    //s_render_t *sMap;
    render_t *rMap;

    //s_render_t *csMap;

    ClientMap *clientMap;
    wchar_t * return_string;
    tpl_node *tn;


public:

    ClientMapPacker();
    void associateClientMap(ClientMap *cMap);
    
    s_render_t clientToSerial(render_t source);
    render_t serialToClient(s_render_t lMap);

    void packToNet(render_t source, unsigned char *buf);
    void unpackFromNet(ClientMap *client, unsigned char *buf, GraphicsTCOD *screen);
    //void initClientMap(ClientMap *dest);


};
