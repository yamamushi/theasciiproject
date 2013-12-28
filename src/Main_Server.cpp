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

#include "FunctionUtils.h"
#include "ConfigParser.h"
#include "ServerSocket.h"
#include "DBConnector.h"
#include "WorldMap.h"
#include "TileMap.h"

namespace po = boost::program_options;

DBConnector *dbEngine;
WorldMap *worldMap;


// Lets's Rock n' Roll

int main(int ac, char* av[]){
    
    // Yeah, I know this isn't the best way to do this, but YAY STREAMS
    std::cout << "The ASCII Project Server - 0.0.1f" << std::endl;
    std::cout << "--------------------------------" << std::endl;
    std::cout << std::endl;

    
    /* Launch a Configuration Parser object using argc and argv.
     Parse isn't part of the constructor in case we want to do
     something else with one we create.
     */
     
    ConfigParser *cfgParse = new ConfigParser(ac, av);
    cfgParse->parse();
    
    // Setup our Database Engine
    dbEngine = new DBConnector(cfgParse->db_hostname, cfgParse->db_port, cfgParse->db_username, cfgParse->db_pass, cfgParse->db_name);    
    
    // Check if World Index exists, if not, we create one.
    if(!fileExists("data/maps/World.idx")){
        worldMap = new WorldMap(cfgParse->worldX, cfgParse->worldY, cfgParse->worldZ);
        worldMap->initWorldMap();
        worldMap->backupToDisk();
        
        std::ofstream indexOutStream("data/maps/World.idx");
        boost::archive::binary_oarchive indexOut(indexOutStream);
        indexOut << worldMap;
        indexOutStream.close();
    }
    else{
        
        std::ifstream indexStream("data/maps/World.idx");
        boost::archive::binary_iarchive indexLoad(indexStream);
        indexLoad >> worldMap;
        
        worldMap->loadFromDisk();
        
    }
    

    try
    {
        std::cout << "Preparing to start listening on port " << cfgParse->serverPort;
        sleep(0.5);
        std::cout << ".";
        sleep(0.5);
        std::cout << ".";
        sleep(0.5);
        std::cout << "." << std::endl;
        
        boost::asio::io_service io_service;
        tcp::endpoint endpoint(tcp::v4(), cfgParse->serverPort);
        boost::asio::signal_set signals(io_service, SIGINT, SIGTERM);
        signals.async_wait(boost::bind(&boost::asio::io_service::stop, &io_service));
        game_server server(io_service, endpoint);
        
        std::cout << "Server startup complete, have fun!" << std::endl;
        std::cout << std::endl;
        
        io_service.run();
    }
    catch (std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }
    
    return 0;
}
