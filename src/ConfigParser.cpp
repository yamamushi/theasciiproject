/*
 * =====================================================================================
 *
 *       Filename:  ConfigParser.cpp
 *
 *    Description:  This class parses the server.conf file for startup variables.
 *
 *        Version:  1.0
 *        Created:  11/21/2012 01:23:29 AM
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

namespace po = boost::program_options;



ConfigParser::ConfigParser(int ac_, char* av_[]){
    
    ac = ac_;
    av = av_;
    
    boost::filesystem::path dataDir("data");
    boost::filesystem::path mapDir("data/maps");
    boost::filesystem::path entDir("data/ents");
    
    if(!boost::filesystem::exists(dataDir))
        boost::filesystem::create_directory(dataDir);
    
    if(!boost::filesystem::exists(mapDir))
        boost::filesystem::create_directory(mapDir);
    
    if(!boost::filesystem::exists(entDir))
        boost::filesystem::create_directory(entDir);
    
    
    
}





void ConfigParser::parse(){
    
    try {
        
        po::options_description desc("Allowed options");
        desc.add_options()
        ("config,c", po::value<std::string>(&config_file)->default_value("server.conf"),"Configuration file, default server.conf")
        ("help,h", "display this help text")
        ("version,v", "display version number")
        ;
        
        po::options_description config("Config File Options");
        config.add_options()
        ("dbhost", po::value<std::string>(&db_hostname)->default_value("localhost"),"Database Hostname")
        ("dbport", po::value<int>(&db_port)->default_value(5432), "Database Port")
        ("dbuser", po::value<std::string>(&db_username), "Database Username")
        ("dbpass", po::value<std::string>(&db_pass), "Database Password")
        ("dbname", po::value<std::string>(&db_name)->default_value(db_username), "Database Name")
        ;
        
        po::options_description hidden("Hidden options");
        hidden.add_options()
        ("server_port", po::value<int>(&serverPort)->default_value(5250), "Server Listening Port")
        ("world_length", po::value<int>(&worldX)->default_value(10), "World Length")
        ("world_depth", po::value<int>(&worldY)->default_value(10), "World Depth")
        ("world_height", po::value<int>(&worldZ)->default_value(10), "World Height")
        ;
         
        po::options_description config_file_options;
        config_file_options.add(config).add(hidden);
        
        po::variables_map vm;
        po::store(po::parse_command_line(ac, av, desc), vm);
        po::notify(vm);
        
        if (vm.count("help")) {
            std::cout << desc << std::endl;
            std::cout << config << std::endl;
            exit(0);
        }
        if (vm.count("version")) {
            std::cout << "The ASCII Project - Server - Version 0.0.0j" << std::endl;
            exit(0);
        }
        
        
        std::ifstream ifs(config_file.c_str());
        if(!ifs)
        {
            std::cout << "could not open config file: " << config_file << std::endl;
            std::cout << "Usage:" << std::endl;
            std::cout << desc << std::endl;
            std::cout << config << std::endl;
            exit(0);
        }
        else
        {
            store(parse_config_file(ifs, config_file_options), vm);
            notify(vm);
        }
        
        std::cout << "DB Host is: " << db_hostname << std::endl << std::endl;
        
        
    }
    catch(std::exception& e) {
        std::cerr << "error: " << e.what() << "\n";
        exit(1);
    }
    catch(...) {
        std::cerr << "Exception of unknown type!\n";
    }
    
    
}














