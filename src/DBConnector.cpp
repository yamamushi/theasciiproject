
#include "Headers.h"


DBConnector::DBConnector(std::string host, int port, std::string user, std::string pass)
{
    
    db_host = host;
    
    
    
    std::stringstream tmpstream;
    tmpstream << port;
    
    db_port = tmpstream.str();
    
    db_user = user;
    db_pass = pass;
    
    ValidateSchema();
    
}

pqxx::work *DBConnector::PrepareConn()
{
    
    pqxx::connection conn("host=" + db_host + " port=" + db_port + " user=" + db_user + " password=" + db_pass + " dbname=ascii");
    
    pqxx::work *dbWorker = new pqxx::work(conn);
    
    return dbWorker;
    
}


void DBConnector::ValidateSchema()
{
    
    try
    {
      
        //pqxx::work *schemaCheck = PrepareConn();
        
        pqxx::connection conn("host=" + db_host + " port=" + db_port + " user=" + db_user + " password=" + db_pass + " dbname=ascii");
        
        pqxx::work schemaCheck(conn);
        
        schemaCheck.exec("DROP SCHEMA IF EXISTS accountingschema");
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



void DBConnector::AddAccount()
{
    
}

void DBConnector::GenerateHash()
{
    
}

void DBConnector::GenerateToken()
{
    
}


bool DBConnector::isValidHash()
{
    return true;
}

bool DBConnector::isValidToken()
{
    return true;
}


void DBConnector::testShared()
{
    
    cout << "Working" << endl;
    
}