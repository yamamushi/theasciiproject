#pragma once
/*
 
 FileLogger.h
 
 Jonathan Rumion (Yamamushi)
 02-07-2013
 
 
 An interface for logging to files.
 
 Specifically, error.log, etc. :)
 
 */

#include <string>
#include <mutex>


class FileLogger {
    
private:
    
    std::string fsPath;
    std::mutex errorLogMutex;
    
public:
    
    FileLogger(std::string FSPath) : fsPath(FSPath) {};
    virtual ~FileLogger(){};
    
    void ErrorLog(std::string message);
    void APILog(std::string message);
    
    
};



