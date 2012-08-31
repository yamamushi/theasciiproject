#include <iostream>
#include <fstream>
#include <string>
#include "BoostLibs.h"

#include "DBConnector.h"
#include "Entities.h"

using std::string;
using std::cout;
using std::endl;



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
            
            std::cerr << "root account does not exist" << endl;
            
            
            time_t rawtime;
            
            struct tm * timeinfo;
            time( &rawtime );
            timeinfo = localtime(&rawtime);
            string loctime = asctime(timeinfo);
            
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
        string loctime = asctime(timeinfo);
        
        srand((unsigned int)time(NULL));
        
        std::stringstream tmpstream;
        tmpstream << rand();
        
        addAccount.exec("INSERT INTO accounting (username, timestamp, hash, filename) VALUES ('" + cleanUser + "', '" + loctime + "', MD5('"  + cleanPass + "'), '" + cleanUser + ".dat');" );
        addAccount.commit();
        
        Entity rawEntity(cleanUser, L"\u263A", 0, 0, 0.0, 0.0, 1.0);
        
        std::ofstream ofs("data/ents/" + cleanUser + ".dat");
        boost::archive::binary_oarchive oa(ofs);
        oa << rawEntity;
        ofs.close();
        
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
        string loctime = asctime(timeinfo);
        
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
        return string("invalid Credentials");
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
            cout << "invalid token" << endl;
            return false;
        }
        else
        {
            cout << "valid token" << endl;
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
    
    cout << "Working" << endl;
    
}
