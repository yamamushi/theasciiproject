/*
 
 ConsoleLog
 Yamamushi (Jon Rumion)
 12 - 30 - 2012
 
 */

#include "ConsoleLog.h"
#include <string>
#include <iostream>
#include <time.h>


void ConsoleLog::Print( std::string message){
    
    time_t now = time(0);
    tm* currentlocaltime = localtime(&now);

    char timestamp[23];
    strftime(timestamp, 23, "%Y-%m-%d %H:%M:%S - ", currentlocaltime);
    
    std::cout << timestamp + message << std::endl;
    
}
