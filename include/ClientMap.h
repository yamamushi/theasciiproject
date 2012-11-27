#pragma once
/*
 * =====================================================================================
 *
 *       Filename:  ClientMap.h
 *
 *    Description:  This object stores the Symbol and Color information
 *              for use in our Client-Side Graphics Rendering library.
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


#include <list>

#include "BoostLibs.h"
#include "constants.h"

class ClientMap {
    
private:
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version)
    {
        ar & cMap;
    }
    
    render_t *cTemp;
    std::list< std::pair<int,int> > ignoreList;
    
public:
    
    
    render_t *cMap[MAP_WIDTH][MAP_HEIGHT];
    
    ClientMap();
    void initClientMap();
    
    void clearMap();
    void cleanMap();
    void deleteMap();
    void clientRefresh();
    
    void refreshSquare(int x, int y);
    void removeSquare(int x, int y);
    void createSquare(int x, int y);
    
    
    void addIgnore(int x, int y);
    bool testIgnore(int x, int y);
    void clearIgnore();
    
    
    
    
    void importSquare(int x, int y, render_t *square);
    render_t *exportSquare(int x, int y);
    
    wchar_t *getSymbol(int x, int y);
    float returnH(int x, int y);
    float returnHD(int x, int y);
    float returnS(int x, int y);
    float returnSD(int x, int y);
    float returnV(int x, int y);
    float returnVD(int x, int y);
    bool returnExplored(int x, int y);
    bool returnOccupied(int x, int y);
    bool returnVisible(int x, int y);
    
};
