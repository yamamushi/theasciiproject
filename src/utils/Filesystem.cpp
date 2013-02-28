/*
 
 FileSystem
 
 Jonathan Rumion (Yamamushi)
 02-05-2013
 
 */

#include "../utils/ConsoleLog.h"
#include "Filesystem.h"
#include <boost/filesystem.hpp>
#include <exception>
#include <iostream>

FileSystem::FileSystem(){
    
}


void FileSystem::MkDir(std::string path){
    
    boost::filesystem::path newDir(path);
    
    if(CheckExists(path)){
        ConsoleLog::Print("Failed to create directory: " +
                          path + " - Directory Already Exists");
    }
    else {
        try {
            boost::filesystem::create_directory(newDir);
        }
        catch(std::exception& e) {
            std::cerr << "error: " << e.what() << std::endl;
            exit(1);
        }
        catch(...){
            std::cerr << "Exception of unknown type!" << std::endl;
            exit(1);
        }
    }
    
    return;
    
}


bool FileSystem::CheckExists(std::string path){
    
    boost::filesystem::path checkFile(path);
    
    if(boost::filesystem::exists(checkFile)){
        return true;
    }
    else
        return false;
    
}
