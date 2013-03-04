/*
 
 FileLogger.cpp
 
 Jonathan Rumion (Yamamushi)
 02-07-2013
 
 */

#include "FileLogger.h"

#include <iostream>
#include <fstream>
#include <time.h>


void FileLogger::ErrorLog(std::string message){
    
    errorLogMutex.lock();
    std::ofstream errorFile;
    errorFile.open(fsPath + "/logs/error.log", std::ios_base::app);
    
    time_t now = time(0);
    
    tm* currentlocaltime = localtime(&now);
    
    char timestamp[23];
    strftime(timestamp, 23, "%Y-%m-%d %H:%M:%S - ", currentlocaltime);
    
    errorFile << timestamp << message << std::endl;
    errorFile.close();
    errorLogMutex.unlock();
    return;
    
}


void FileLogger::WorldLog(std::string message){
    
    worldLogMutex.lock();
    std::ofstream errorFile;
    errorFile.open(fsPath + "/logs/world.log", std::ios_base::app);
    
    time_t now = time(0);
    
    tm* currentlocaltime = localtime(&now);
    
    char timestamp[23];
    strftime(timestamp, 23, "%Y-%m-%d %H:%M:%S - ", currentlocaltime);
    
    errorFile << timestamp << message << std::endl;
    errorFile.close();
    worldLogMutex.unlock();
    return;
    
}