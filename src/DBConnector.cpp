/*
 * =====================================================================================
 *
 *       Filename:  DBConnector.cpp
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



#include <iostream>
#include <fstream>
#include <string>
#include "BoostLibs.h"

#include "FunctionUtils.h"
#include "DBConnector.h"
#include "Entities.h"




DBConnector::DBConnector(std::string host, int port, std::string user, std::string pass, std::string db)
{
    
    db_host = host;
    
    std::stringstream tmpstream;
    tmpstream << port;
    
    std::string dbport = tmpstream.str();
    db_port = dbport;
    
    db_user = user;
    db_pass = pass;
    db_name = db;
    
    std::cout << "Database Connection Settings" << std::endl;
    std::cout << "----------------------------" << std::endl;
    std::cout << "DB Host: " << db_host << std::endl;
    std::cout << "DB Port: " << db_port << std::endl;
    std::cout << "DB User: " << db_user << std::endl;
    std::cout << std::endl;
    
    
    ValidateSchema();
    
}



void DBConnector::ValidateSchema()
{
    
    try
    {
        
        pqxx::asyncconnection conn("host=" + db_host + " port=" + db_port + " user=" + db_user + " password=" + db_pass + " dbname=" + db_name);
        
        pqxx::work schemaCheck(conn);
        
        
        schemaCheck.exec("CREATE TABLE IF NOT EXISTS accounting(id SERIAL PRIMARY KEY, username varchar(16), timestamp timestamp(6), hash varchar(255), token varchar(255), filename varchar(255));");
        
        
        pqxx::result rootCheck = schemaCheck.exec("SELECT id FROM accounting WHERE username = 'root'");
        
        if (rootCheck.size() != 1)
        {
            
            std::cerr << "root account does not exist" << std::endl;
            
            
            time_t rawtime;
            
            struct tm * timeinfo;
            time( &rawtime );
            timeinfo = localtime(&rawtime);
            std::string loctime = asctime(timeinfo);
            
            srand((unsigned int)time(NULL));
            
            std::stringstream tmpstream;
            tmpstream << rand();
            
            
            schemaCheck.exec("INSERT INTO accounting (username, timestamp, hash) VALUES ('root', '" + loctime + "', MD5('"  + tmpstream.str() + "'));" );
            
            hasRootAccount = true;
        }
        
        schemaCheck.commit();
        
    }
    catch(const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
        
    }
    catch(...)
    {
        std::cerr << "Unknown Exception in DBConnector::ValidateSchema()" << std::endl;
    }
    
    
}



bool DBConnector::AddAccount(const std::string user, const std::string pass)
{
    
    boost::regex e("[\\']");
    std::string cleanUser = boost::regex_replace(user, e, "");
    std::string cleanPass = boost::regex_replace(pass, e, "");
    
    pqxx::asyncconnection conn("host=" + db_host + " port=" + db_port + " user=" + db_user + " password=" + db_pass + " dbname=" + db_name);
    pqxx::work addAccount(conn);
    
    pqxx::result doesAccountExist = addAccount.exec("SELECT id FROM accounting WHERE username='" + cleanUser + "';");
    
    if(doesAccountExist.size() != 1)
    {
        
        time_t rawtime;
        
        struct tm * timeinfo;
        time( &rawtime );
        timeinfo = localtime(&rawtime);
        std::string loctime = asctime(timeinfo);
        
        srand((unsigned int)time(NULL));
        
        std::stringstream tmpstream;
        tmpstream << rand();
        
        addAccount.exec("INSERT INTO accounting (username, timestamp, hash, filename) VALUES ('" + cleanUser + "', '" + loctime + "', MD5('"  + cleanPass + "'), '" + cleanUser + ".dat');" );
        addAccount.commit();
        
        Entity *rawEntity = new Entity(cleanUser, L"\u263A", 0, 0, 0, 0, 0, 0.0, 0.0, 1.0);
        
        std::string filePath("data/ents/" + cleanUser + ".dat");
        
        if(!fileExists(filePath)){
            std::ofstream ofs(filePath);
            boost::archive::binary_oarchive oa(ofs);
            oa << rawEntity;
            ofs.close();
        }
        delete rawEntity;
        return true;
    }
    else
    {
        addAccount.commit();
        return false;
    }
    
    
}

bool DBConnector::isValidHash(const std::string user, const std::string pass)
{
    
    std::string User, Pass;
    User = user;
    Pass = pass;
    
    
    boost::regex e("[\\']");
    std::string cleanUser = boost::regex_replace(User, e, "");
    std::string cleanPass = boost::regex_replace(Pass, e, "");
    
    pqxx::asyncconnection conn("host=" + db_host + " port=" + db_port + " user=" + db_user + " password=" + db_pass + " dbname=" + db_name);
    pqxx::work validatePass(conn);
    
    pqxx::result doesAccountExist = validatePass.exec("SELECT id FROM accounting WHERE username='" + cleanUser + "';");
    
    if(doesAccountExist.size() != 1)
    {
        
        validatePass.commit();
        return false;
        
    }
    else
    {
        
        pqxx::result md5hash = validatePass.exec("SELECT hash FROM accounting WHERE username='" + cleanUser + "';");
        pqxx::result tmphash = validatePass.exec("SELECT MD5('" + cleanPass + "');");
        
        validatePass.commit();
        
        std::string md5pass = md5hash[0][0].as<std::string>();
        std::string tmpHash = tmphash[0][0].as<std::string>();
        
        if ( md5pass.compare(tmpHash) != 0)
        {
            // cout << "invalid pass" << endl;
            return false;
        }
        else
        {
            // cout << "valid pass" << endl;
            return true;
        }
        
        
    }
    
}

std::string DBConnector::GenerateToken(const std::string user, const std::string pass)
{
    
    boost::regex e("[\\']");
    std::string cleanUser = boost::regex_replace(user, e, "");
    std::string cleanPass = boost::regex_replace(pass, e, "");
    
    if(isValidHash(cleanUser, cleanPass))
    {
        pqxx::asyncconnection conn("host=" + db_host + " port=" + db_port + " user=" + db_user + " password=" + db_pass + " dbname=" + db_name);
        pqxx::work tokenGenerator(conn);
        
        pqxx::result md5hash = tokenGenerator.exec("SELECT hash FROM accounting WHERE username='" + cleanUser + "';");
        std::string md5pass = md5hash[0][0].as<std::string>();
        
        
        time_t rawtime;
        
        struct tm * timeinfo;
        time( &rawtime );
        timeinfo = localtime(&rawtime);
        std::string loctime = asctime(timeinfo);
        
        srand((unsigned int)time(&rawtime));
        
        std::stringstream tmpstream;
        tmpstream << rand();
        
        std::string tokenizeMe = md5pass;
        tokenizeMe += tmpstream.str();
        tokenizeMe += loctime;
        
        
        pqxx::result token = tokenGenerator.exec("SELECT MD5('" + tokenizeMe + "');");
        
        std::string finalToken = token[0][0].as<std::string>();
        
        
        tokenGenerator.exec("UPDATE accounting SET token='" + finalToken + "' WHERE username='" + cleanUser + "';");
        
        tokenGenerator.commit();
        
        return finalToken;
        
    }
    else
    {
        return std::string("invalid Credentials");
    }
}


bool DBConnector::isValidToken(const std::string user, const std::string token)
{
    boost::regex e("[\\']");
    std::string cleanUser = boost::regex_replace(user, e, "");
    std::string cleanPass = boost::regex_replace(token, e, "");
    
    
    pqxx::asyncconnection conn("host=" + db_host + " port=" + db_port + " user=" + db_user + " password=" + db_pass + " dbname=" + db_name);
    pqxx::work validateToken(conn);
    
    pqxx::result doesAccountExist = validateToken.exec("SELECT id FROM accounting WHERE username='" + cleanUser + "';");
    
    if(doesAccountExist.size() != 1)
    {
        
        validateToken.commit();
        return false;
        
    }
    else
    {
        
        pqxx::result RealToken = validateToken.exec("SELECT token FROM accounting WHERE username='" + cleanUser + "';");
        
        validateToken.commit();
        
        std::string realToken = RealToken[0][0].as<std::string>();
        
        
        if ( realToken.compare(token) != 0)
        {
            std::cout << "invalid token" << std::endl;
            return false;
        }
        else
        {
            std::cout << "valid token" << std::endl;
            return true;
        }
        
        
    }
    
    
    
}


std::string DBConnector::getDatFilename(const std::string user, const std::string token)
{
    if(isValidToken(user, token))
    {
        pqxx::asyncconnection conn("host=" + db_host + " port=" + db_port + " user=" + db_user + " password=" + db_pass + " dbname=" + db_name);
        pqxx::work getFilename(conn);
        
        boost::regex e("[\\']");
        std::string cleanUser = boost::regex_replace(user, e, "");
        std::string cleanPass = boost::regex_replace(token, e, "");
        
        pqxx::result doesFilenameExist = getFilename.exec("SELECT filename FROM accounting WHERE username='" + cleanUser + "';");
        
        std::string filename = doesFilenameExist[0][0].as<std::string>();
        
        return filename;
        
        
    }
    else
    {
        return "ERROR";
    }
    
    
}


void DBConnector::testShared()
{
    
    std::cout << "Working" << std::endl;
    
}
