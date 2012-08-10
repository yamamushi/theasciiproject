
#include "Headers.h"
#include <iostream>
#include <pqxx/pqxx>
#include "DBConnector.h"

DBConnector::DBConnector(std::string host, std::string port, std::string user, std::string pass)
{
    
    db_host = host;
    db_port = port;
    db_user = user;
    db_pass = pass;
    
}