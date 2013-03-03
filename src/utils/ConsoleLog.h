#pragma once
/*
 
 ConsoleLog
 
 A set of logging functions so that we don't have to include <iostream> in every other file.
 
 - Yamamushi (Jon Rumion)
 2012 - 12 - 30
 
 */



#include <string>


class ConsoleLog {
    
private:    
    
public:
    
    ConsoleLog(){};
    virtual ~ConsoleLog(){};
    
    static void Print( std::string );
    
};
