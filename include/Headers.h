/*
 * =====================================================================================
 *
 *       Filename:  Headers.h
 *
 *    Description:  An attempt to consolidate and order our header files
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


// Our global constants
#include "constants.h"


// Standard Library headers
#ifndef __MINGW32__
#include <arpa/inet.h>   /* ntohl htonl */
#endif

#include <math.h>
#include <algorithm>
#include <iostream>
#include <vector>
#include <typeinfo>
#include <map>
#include <list>
#include <set>
#include <deque>
#include <ctime>
#include <string>
#include <mutex>
#include <future>
#include <iterator>
#include <cstring>
#include <wchar.h>
#include <clocale>
#include <cstdlib>
#include <stddef.h>
#include <inttypes.h>
#include <sstream>
#include <time.h>
#include <fstream>
#include <regex>
#include <stdarg.h>

// postgresql connector
//#include <pqxx/pqxx> /* Moved to ServerSocket.cpp */

// Now's a good time to bring in Boost
// Which we'll store references to here
#include "BoostLibs.h"
namespace po = boost::program_options;

// Implementing the tpl serialization library
#include "tpl.h"
#include "Serialization.h"

// Our namespaces
// Or rather, just std at this time :-)
using namespace std;
using boost::asio::ip::tcp;


// 3rd party local headers
#include "libtcod/libtcod.hpp"
#include "libtcod/gui/gui.hpp"
#include "ui_input.hpp"


// Our most important objects
#include "Tiles.h"
#include "TileMap.h"
#include "Entities.h"
#include "EntityMap.h"

// Our standalone engine libraries
#include "FovLib.h"


// Temporary Dungeon Generator
#include "Dungeon.h"


// This will be rewritten "soon"
#include "Keyboard.h"
//#include "DBConnector.h" /* Moved to ServerSocket.cpp */



// Collect.h holds our data
// Collection functions
#include "Collect.h"



// Graphics Stuff
#include "RenderMap.h"
#include "ClientMap.h"
#include "ClientWidgets.h"
#include "Graphics.h"


// Following the OSI model
// Our Network Layer should
// Always go last
#include "ClientSocket.h"































