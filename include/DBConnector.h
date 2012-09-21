/*
 * =====================================================================================
 *
 *       Filename:  DBConnector.h
 *
 *    Description:  This object defines the behavior of our "Entities", ie
 *                  The necessary functions for an entity to exist on the "Map"
 *
 *        Version:  1.0
 *        Created:  07/03/2012 03:41:29 AM
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



#include <pqxx/pqxx>


class DBConnector {
    
private:
    

    
    
    bool hasRootAccount;
    
    void ValidateSchema();
    
public:
    
    std::string db_host;
    std::string db_port;
    std::string db_user;
    std::string db_pass;
    std::string db_name;
    
    DBConnector(std::string host, int port, std::string user, std::string pass, std::string db);
    
    pqxx::work *PrepareConn();
    
    
    
    bool AddAccount(const std::string user, const std::string pass);

    
    bool isValidHash(const std::string user, const std::string pass);
    
    std::string GenerateToken(const std::string user, const std::string pass);
    bool isValidToken(const std::string user, const std::string token);
    
    std::string getDatFilename(const std::string user, const std::string token);
    
    void testShared();
    
    
};