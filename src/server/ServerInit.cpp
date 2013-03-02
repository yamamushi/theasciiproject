/*
 
 ServerInit
 
 Jonathan Rumion (Yamamushi)
 02-05-2013
 
 
 */

#include <string>
#include <iostream>
#include <thread>
#include <exception>

#include "ServerInit.h"
#include "../db/MySQLServerDB.h"
#include "../networking/Boost_Net_Asio.h"
#include "../networking/TCP_Handler.h"
#include "../utils/ConsoleLog.h"
#include "../utils/FileLogger.h"
#include "../utils/Filesystem.h"
#include "../parsers/ServerConfig.h"
#include "../worldgen/WorldgenInit.h"


FileLogger *fileLogger;


void ServerInit(int argc, char *argv[]){
    
    ServerConfigParser *serverConfig = new ServerConfigParser( argc, argv);
    serverConfig->Parse();
    
    DirectoryInit(serverConfig->data_dir);
    
    fileLogger = new FileLogger(serverConfig->data_dir);
    fileLogger->ErrorLog("Server Configuration Read");
    
    std::thread mysql( MySQLDBInit, serverConfig->db_hostname, serverConfig->db_port, serverConfig->db_username, serverConfig->db_pass, serverConfig->db_name );
    
    WorldGen *worldGen = new WorldGen(serverConfig);
    std::thread worldgen(&WorldGen::init, worldGen);
    
    // Break off our Net Initialization
    std::thread tcp_listener(NetInit, serverConfig->server_port);
    
    
    mysql.join();
    worldgen.join();
    tcp_listener.join();
    
    return;
    
}


void DirectoryInit(std::string rootFSPath){
    
    if(!FileSystem::CheckExists(rootFSPath)){
        FileSystem::MkDir(rootFSPath);
    }
    if(!FileSystem::CheckExists(rootFSPath + "/ents")){
        FileSystem::MkDir(rootFSPath + "/ents");
    }
    if(!FileSystem::CheckExists(rootFSPath + "/logs")){
        FileSystem::MkDir(rootFSPath + "/logs");
    }
    if(!FileSystem::CheckExists(rootFSPath + "/maps")){
        FileSystem::MkDir(rootFSPath + "/maps");
    }
    if(!FileSystem::CheckExists(rootFSPath + "/players")){
        FileSystem::MkDir(rootFSPath + "/players");
    }
    if(!FileSystem::CheckExists(rootFSPath + "/scripts")){
        FileSystem::MkDir(rootFSPath + "/scripts");
    }
    
    return;
    
}


void MySQLDBInit(std::string hostname, int port, std::string username, std::string pass, std::string database) {
    
    fileLogger->ErrorLog("MySQL Database Initializing");
    MySQLServerDB dbConnector(hostname, port, username, pass, database);
    
    dbConnector.PrintVersion();
    
    // We create our Users table, it doesn't matter if it exists or not
    // Because we're not going to magically overwrite any existing data.
    
    dbConnector.Query("CREATE TABLE users(ID int NOT NULL AUTO_INCREMENT, PRIMARY KEY(id), username VARCHAR(255), pass BINARY(32), email VARCHAR(255), registered DATETIME)");
    
    //  Int Results = Dbconnector.RowCount("SELECT * from users");
    // std::cout << results << std::endl;
    
    fileLogger->ErrorLog("MySQL Database Initialized");
    
    return;
    
}


void NetInit(int port){
    
    try {
        
        boost::asio::io_service io_service;
        boost::asio::signal_set signals(io_service, SIGINT, SIGTERM);
        tcp_handler_ptr tcp_server(new TCP_Handler(io_service, port));
        io_service.run();
        
    }
    catch(std::exception& e){
        
        std::cerr << "Exception: " << e.what() << std::endl;
        
    }
    
}
