/*
 * =====================================================================================
 *
 *       Filename:  ConfigParser.h
 *
 *    Description:  Class definitions for our Startup Config Parser
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




class ConfigParser {
    
private:
    int ac;
    char** av;
    
    std::string config_file;
    
public:
    
    ConfigParser(int ac_, char* av_[]);
    virtual ~ConfigParser(){};
    
    // Organized a little differently than I do usually
    // (which is probably annoying for most people reading my code)
    // Our program options are going to be listed here
    
    int db_port;
    std::string db_hostname;
    std::string db_username;
    std::string db_pass;
    std::string db_name;
    
    int serverPort;
    int worldX;
    int worldY;
    int worldZ;
    
    void parse();
    
    
};

