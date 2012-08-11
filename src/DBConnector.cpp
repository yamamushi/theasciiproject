
#include "Headers.h"


DBConnector::DBConnector(std::string host, int port, std::string user, std::string pass)
{
    
    db_host = host;
    db_port = port;
    db_user = user;
    db_pass = pass;
   
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