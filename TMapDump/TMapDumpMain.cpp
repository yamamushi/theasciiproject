//
//  main.c
//  TMapDump
//
//  Created by Jonathan Rumion on 3/2/13.
//  Copyright (c) 2013 TAP. All rights reserved.
//
//  This utility is used to dump TileMap files to console
//
//


#include <iostream>
#include <fstream>
#include <exception>
#include <vector>
#include <locale>
#include <boost/program_options.hpp>
#include <boost/filesystem.hpp>
#include "../src/serialization/Boost_Serialization.h"
#include "../src/mapping/Tile.h"
#include "../src/mapping/TileMap.h"

namespace po = boost::program_options;


int main(int argc, const char * argv[])
{
    std::string tilemap_path;
    std::string path;
    
    setlocale(LC_ALL,"");
    
    
    // Print Options
    try{
        
        po::options_description desc("Allowed Options");
        desc.add_options()
        ("tilemap,t", po::value<std::string>(&tilemap_path),"TileMap File to Dump")
        ("help,h", "Display this help text")
        ("version,v", "Display version number")
        ;
        
        po::variables_map vm;
        po::store(po::parse_command_line(argc, argv, desc), vm);
        po::notify(vm);
        
        if(vm.count("help")){
            std::cout << desc << std::endl;
            exit(0);
        }
        if(vm.count("version")){
            std::cout << "TMapDump - 0.1" << std::endl;
            exit(0);
        }
        
        boost::filesystem::path filePath(tilemap_path);
        if(!boost::filesystem::exists(filePath)){
            std::cout << "Error" << std::endl;
            std::cout << "TileMap file \"" << tilemap_path << "\" does not exist." << std::endl;
            std::cout << "Please check your syntax and try again." << std::endl;
            exit(0);
        }
        
        std::ifstream ifs(tilemap_path.c_str());
        if(!ifs){
            std::cout << "TMapDump is a utility for dumping raw TileMap files to console." << std::endl << std::endl;
            std::cout << desc << std::endl;
            exit(0);
        }
        
    }
    catch(std::exception& e){
        std::cerr << "error: " << e.what() << std::endl;
        exit(1);
    }
    catch(...){
        std::cerr << "Exception of unknown type!" << std::endl;
    }
    
    std::cout << "Now reading TileMap " << tilemap_path << std::endl;
    
    // Read Map from File
    std::ifstream inputMap(tilemap_path);
    boost::archive::text_iarchive inputTextArchive(inputMap);
    
    TileMap *outputMap;
    
    inputTextArchive & outputMap;
    
    std::cout << "Map Length: " << outputMap->getLength() << " Tiles" << std::endl;
    std::cout << "Map Width: " << outputMap->getWidth() << " Tiles" << std::endl;
    
    for(int x=0; x<outputMap->getLength(); x++){
        for(int y=0; y<outputMap->getWidth(); y++){
            
            try{
                std::cout << outputMap->virtualMap.at(x).at(y)->getSymbol();
            }
            catch(std::exception& e){
                std::cerr << "error: " << e.what() << std::endl;
                exit(1);
            }
            catch(...){
                std::cerr << "Exception of unknown type!" << std::endl;
            }
        }
        
        std::cout << std::endl;
    }
    
    
    
    // Dump Map to Console
    return 0;
}

