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

// First our custom headers
#include "Headers.h"
#include "ServerSocket.h"
#include "DBConnector.h"

DBConnector *dbEngine;
EntityMap *entMap;


// Lets's Rock n' Roll

int main(int ac, char* av[]){
    
    boost::filesystem::path dataDir("data");
    boost::filesystem::path mapDir("data/maps");
    boost::filesystem::path entDir("data/ents");
    
    if(!boost::filesystem::exists(dataDir))
        boost::filesystem::create_directory(dataDir);
    
    if(!boost::filesystem::exists(mapDir))
        boost::filesystem::create_directory(mapDir);
    
    if(!boost::filesystem::exists(entDir))
        boost::filesystem::create_directory(entDir);
    
    
    
    
    
    int db_port;
    std::string db_hostname;
    std::string db_username;
    std::string db_pass;
    std::string db_name;
    std::string config_file;
    
    try {
        
        po::options_description desc("Allowed options");
        desc.add_options()
        ("config,c", po::value<std::string>(&config_file)->default_value("server.conf"),"Configuration file, default server.conf")
        ("help,h", "display this help text")
        ("version,v", "display version number")
        ;
        
        po::options_description config("Config File Options");
        config.add_options()
        ("host", po::value<std::string>(&db_hostname)->default_value("localhost"),"Database Hostname")
        ("port", po::value<int>(&db_port)->default_value(5432), "Database Port")
        ("username", po::value<std::string>(&db_username), "Database Username")
        ("dbpass", po::value<std::string>(&db_pass), "Database Password")
        ("dbname", po::value<std::string>(&db_name)->default_value(db_username), "Database Name")
        ;
        
        po::options_description config_file_options;
        config_file_options.add(config);
        
        po::variables_map vm;
        po::store(po::parse_command_line(ac, av, desc), vm);
        po::notify(vm);
        
        if (vm.count("help")) {
            cout << desc << endl;
            cout << config << endl;
            exit(0);
        }
        if (vm.count("version")) {
            cout << "The ASCII Project - Server - Version 0.0.0j" << endl;
            exit(0);
        }
        
        
        std::ifstream ifs(config_file.c_str());
        if(!ifs)
        {
            cout << "could not open config file: " << config_file << endl;
            cout << "Usage:" << endl;
            cout << desc << endl;
            cout << config << endl;
            exit(0);
        }
        else
        {
            store(parse_config_file(ifs, config_file_options), vm);
            notify(vm);
        }
        
        cout << "Host is: " << db_hostname << endl;
        

    }
    catch(exception& e) {
        cerr << "error: " << e.what() << "\n";
        return 1;
    }
    catch(...) {
        cerr << "Exception of unknown type!\n";
    }
    

    
    
    
    
    
    dbEngine = new DBConnector(db_hostname, db_port, db_username, db_pass, db_name);
    
    
    
    TileMap *map = new TileMap(MAP_WIDTH, MAP_HEIGHT);
    // Temporary Dungeon Generator
    Dungeon(map, MAP_WIDTH, MAP_HEIGHT, true);
    // init Fov Lib ASAP after TileMap and Dungeon have been initialized.
    FovLib *fovLib = new FovLib(map);
    // Obviously our entity map would depend on FOV being loaded.
    RenderMap *rMap = new RenderMap(map);
    
    entMap = new EntityMap(MAP_WIDTH, MAP_HEIGHT, map, fovLib, rMap);
       
    
    Goblin *goblin = new Goblin();
    entMap->addToMap(goblin);
    
    
    // Entities don't have to be initialized at the same time, they can
    // also be initialized individually.
    
    entMap->initAllEnts();
    
    goblin->move(map->rooms[5]->cX, map->rooms[5]->cY);
    
   // player->move(map->rooms[1]->cX, map->rooms[1]->cY);
    
    
 //   player->associateClient(rMap);
 //   rMap->refreshMap();
    
   // test = player;
    
    
    try
    {
        boost::asio::io_service io_service;
        tcp::endpoint endpoint(tcp::v4(), 5250);
        game_server server(io_service, endpoint);
        io_service.run();
    }
    catch (std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }
    
    
    
    
    return 0;
}
