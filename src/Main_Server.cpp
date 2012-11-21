/*
 * =====================================================================================
 *
 *       Filename:  Main.cpp
 *
 *    Description:  The ASCII Project main loop
 *
 *        Version:  1.0
 *        Created:  07/03/2012 03:04:46 AM
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

#include <iostream>
#include <fstream>
#include <exception>
#include "BoostLibs.h"

#include "ConfigParser.h"
#include "ServerSocket.h"
#include "DBConnector.h"
#include "WorldMap.h"

namespace po = boost::program_options;
using std::cout;
using std::cerr;
using std::endl;

DBConnector *dbEngine;
EntityMap *entMap;
WorldMap *worldMap;


// Lets's Rock n' Roll

int main(int ac, char* av[]){
    
    ConfigParser *cfgParse = new ConfigParser(ac, av);
    cfgParse->parse();
    
    dbEngine = new DBConnector(cfgParse->db_hostname, cfgParse->db_port, cfgParse->db_username, cfgParse->db_pass, cfgParse->db_name);
    
    // Our updated config files are going to need to be the source for
    // WorldMap's initialization variables (10,10,10)...
    worldMap = new WorldMap(10,10,10);
    worldMap->initWorldMap();
    
    

    try
    {
        boost::asio::io_service io_service;
        tcp::endpoint endpoint(tcp::v4(), 5250);
        boost::asio::signal_set signals(io_service, SIGINT, SIGTERM);
        signals.async_wait(boost::bind(&boost::asio::io_service::stop, &io_service));
        game_server server(io_service, endpoint);
        io_service.run();
    }
    catch (std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }
    
    
    
    
    return 0;
}
