/*
 * =====================================================================================
 *
 *       Filename:  FunctionUtils.cpp
 *
 *    Description:  Various freeform functions for working with non-object data
 *
 *        Version:  1.0
 *        Created:  11/22/2012 02:21:00 AM
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

#include <sys/stat.h>
#include <string>
#include <vector>



std::string make_daytime_string()
{
    time_t now = time(0);
    return ctime(&now);
};




bool pointInSquare( int x, int y, int n)
{
    
    
    return (y <= n - x &&
            y >= x - n &&
            y <= x + n &&
            y>= -(x + n));
    
}


bool isInteger(const std::string & s)
{
    if(s.empty() || ((!isdigit(s[0])) && (s[0] != '-') && (s[0] != '+'))) return false ;
    
    char * p ;
    strtol(s.c_str(), &p, 10) ;
    
    return (*p == 0) ;
}



// Function: fileExists
/**
 Check if a file exists
 @param[in] filename - the name of the file to check
 
 @return    true if the file exists, else false
 
 */
bool fileExists(const std::string& filename)
{
    struct stat buf;
    if (stat(filename.c_str(), &buf) != -1)
    {
        return true;
    }
    return false;
}























