/*
 
 MySQLServerDB.cpp
 
 Jonathan Rumion (Yamamushi)
 02-06-2013
 
 */

#include "MySQLServerDB.h"
#include "../utils/FileLogger.h"

#include <exception>
#include <iostream>
#include <string>

#include <my_global.h>
#include <mysql.h>

extern FileLogger *fileLogger;


MySQLServerDB::MySQLServerDB(std::string Hostname, int Port, std::string Username, std::string Pass, std::string Database) : hostname(Hostname), port(Port), username(Username), pass(Pass), database(Database) {
    
    connection = mysql_init(NULL);
    
    if(mysql_real_connect(connection, hostname.c_str(), username.c_str(), pass.c_str(), database.c_str(), port, NULL, 0)){
        ConnectionOpen = true;
        std::cout << "Established MySQL Connection" << std::endl;
    } else {
        ConnectionOpen = false;
        std::cout << "Error: MySQL Connection Failed" << std::endl;
    }
    
}

int MySQLServerDB::RowCount(std::string query){
    
    MYSQL_RES *result;
    int num_rows = 0;
    
    if(!ConnectionOpen){
        std::cout << "Error: Not Connected" << std::endl;
        return num_rows;
    }
    
    try {
        mysql_query(connection, query.c_str() );
        result = mysql_store_result(connection);
        num_rows = (int)mysql_num_rows(result);
        return num_rows;
    }
    catch(std::exception &e){
        std::cerr << "MySQL Database Error: " << e.what() << std::endl;
    }
    catch(...){
        std::cerr << "Exception of unknown type!" << std::endl;
    }
    
    return num_rows;
    
}



void MySQLServerDB::CloseConnection(){
    
    mysql_close(connection);
    return;
    
}


void MySQLServerDB::PrintVersion(){
    
    std::cout << "MySQL Client Version: " << mysql_get_client_info() << std::endl;
    std::cout << "MySQL Server Version: " << mysql_get_server_info(connection) << std::endl;
    return;
    
}

void MySQLServerDB::Query(std::string query){
    
    fileLogger->ErrorLog("MySQL Query: " + query);
    
    if(!ConnectionOpen){
        std::cout << "Error: Not Connected" << std::endl;
        return;
    }
    
    try {
        mysql_query(connection, query.c_str() );
    }
    catch(std::exception &e){
        std::cerr << "MySQL Database Error: " << e.what() << std::endl;
    }
    catch(...){
        std::cerr << "Exception of unknown type!" << std::endl;
    }
    
    return;
    
}

