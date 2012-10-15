//
//  AnsiConstants.h
//  The ASCII Project
//
//  Created by Jonathan Rumion on 10/15/12.
//  Copyright (c) 2012 Jonathan Rumion. All rights reserved.
//

#ifndef The_ASCII_Project_AnsiConstants_h
#define The_ASCII_Project_AnsiConstants_h

#include <string>


const std::string ANSI_RESET("\x1b[0m");
const std::string BOLD("\x1b[1m");
const std::string BRIGHT("\x1b[1m");

const std::string BLINK_ON("\x1b[5m");

const std::string NORMAL("\x1b[22m");

const std::string BLINK_OFF("\x1b[25m");


const std::string FORE_BLACK("\x1b[30m");
const std::string FORE_RED("\x1b[31m");
const std::string FORE_GREEN("\x1b[32m");
const std::string FORE_YELLOW("\x1b[33m");
const std::string FORE_BLUE("\x1b[34m");
const std::string FORE_MAGENTA("\x1b[35m");
const std::string FORE_CYAN("\x1b[36m");
const std::string FORE_WHITE("\x1b[37m");

const std::string DEFAULT_FORE_COLOR("\x1b[39m");

const std::string BACK_BLACK("\x1b[40m");
const std::string BACK_RED("\x1b[41m");
const std::string BACK_GREEN("\x1b[42m");
const std::string BACK_YELLOW("\x1b[43m");
const std::string BACK_BLUE("\x1b[44m");
const std::string BACK_MAGENTA("\x1b[45m");
const std::string BACK_CYAN("\x1b[46m");
const std::string BACK_WHITE("\x1b[47m");

const std::string DEFAULT_BACK_COLOR("\x1b[49m");

#endif
