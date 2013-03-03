//
//  WMapDumpMain.cpp
//  WorldMapDump
//
//  Created by Jonathan Rumion on 3/2/13.
//  Copyright (c) 2013 TAP. All rights reserved.
//
//  This utility is used to dump WorldMap files to console
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
#include "../src/mapping/WorldMap.h"

namespace po = boost::program_options;


int main(int argc, const char * argv[])
{
    std::string worldmap_path;
    std::string path;
    
    int posX, posY, posZ;
    
    setlocale(LC_ALL,"");
    
    
    // Print Options
    try{
        
        po::options_description desc("Allowed Options");
        desc.add_options()
        ("worldmap,w", po::value<std::string>(&worldmap_path),"WorldMap File to Dump")
        ("worldX,x", po::value<int>(&posX)->default_value(0), "X Coordinates of map to dump")
        ("worldY,y", po::value<int>(&posY)->default_value(0), "Y Coordinates of map to dump")
        ("worldZ,z", po::value<int>(&posZ)->default_value(0), "Z Coordinates of map to dump")
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
            std::cout << "WMapDump - 0.1" << std::endl;
            exit(0);
        }
        
       /* boost::filesystem::path filePath(worldmap_path);
        if(!boost::filesystem::exists(filePath)){
            std::cout << "Error" << std::endl;
            std::cout << "WorldMap file \"" << worldmap_path << "\" does not exist." << std::endl;
            std::cout << "Please check your syntax and try again." << std::endl;
            exit(0);
        } */
        
        std::ifstream ifs(worldmap_path.c_str());
        if(!ifs){
            std::cout << "WMapDump is a utility for dumping raw TileMap files to console." << std::endl << std::endl;
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
    
    std::cout << "Now reading WorldMap " << worldmap_path << std::endl;
    
    // Read Map from File
    std::ifstream inputMap(worldmap_path);
    boost::archive::text_iarchive inputBinaryArchive(inputMap);
    
    WorldMap *outputMap;
    
    inputBinaryArchive & outputMap;
    
    std::cout << std::endl;
    
    std::cout << "Map Length: " << outputMap->getX() << " Maps" << std::endl;
    std::cout << "Map Width: " << outputMap->getY() << " Maps" << std::endl;
    std::cout << "Map Height: " << outputMap->getZ() << " Maps" << std::endl;
    std::cout << std::endl;
    
    if(posX > outputMap->getX()){
        std::cout << "X out of Bounds" << std::endl;
        exit(0);
    }
    if(posY > outputMap->getY()){
        std::cout << "Y out of Bounds" << std::endl;
        exit(0);
    }
    if(posZ > outputMap->getZ()){
        std::cout << "Z out of Bounds" << std::endl;
        exit(0);
    }
    

    TileMap outputTileMap;
    
    outputTileMap = *outputMap->getTileMap(posX, posY, posZ);
    
    std::cout << std::endl;
    std::cout << "TileMap Length: " << outputTileMap.getLength() << std::endl;
    std::cout << "TileMap Width: " << outputTileMap.getWidth() << std::endl;
    std::cout << std::endl;
    
    std::cout << "Map at X:" << posX << " Y:" << posY << " Z:" << posZ << std::endl;
        
    for(int x=0; x<outputTileMap.getLength(); x++){
        for(int y=0; y<outputTileMap.getWidth(); y++){
            
            try{
                std::cout << outputTileMap.virtualMap.at(x).at(y)->getSymbol();
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

