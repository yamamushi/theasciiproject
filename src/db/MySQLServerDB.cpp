/*
 
 MySQLServerDB.cpp
 
 Jonathan Rumion (Yamamushi)
 02-06-2013
 
 */

#include "MySQLServerDB.h"
#include "../utils/FileLogger.h"
#include "../utils/ConsoleLog.h"

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
        ConsoleLog::Print("Established MySQL Connection");
    } else {
        ConnectionOpen = false;
        fileLogger->ErrorLog("Error: MySQL Connection Failed");
        ConsoleLog::Print("Error: MySQL Connection Failed");
    }
    
}

int MySQLServerDB::RowCount(std::string query){
    
    MYSQL_RES *result;
    int num_rows = 0;
    
    if(!ConnectionOpen){
        ConsoleLog::Print("Error: MySQL Handler Not Connected");
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
    
    ConsoleLog::Print("MySQL Client Version: " + (std::string)mysql_get_client_info());
    ConsoleLog::Print("MySQL Server Version: " + (std::string)mysql_get_server_info(connection));
    return;
    
}

void MySQLServerDB::Query(std::string query){
    
    fileLogger->ErrorLog("MySQL Query: " + query);
    
    if(!ConnectionOpen){
        ConsoleLog::Print("Error: MySQL Handler Not Connected");
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

