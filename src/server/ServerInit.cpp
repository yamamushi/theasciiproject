/*
 
 ServerInit
 
 Jonathan Rumion (Yamamushi)
 02-05-2013
 
 
 */

#include <string>
#include <iostream>
#include <thread>
#include <memory>
#include <exception>
#include <functional>
#include <locale>

#include "ServerInit.h"
#include "../api/ServerAPI.h"
#include "../db/MySQLServerDB.h"
#include "../engine/WorldEngine.h"
#include "../networking/Boost_Net_Asio.h"
#include "../networking/TCP_Handler.h"
#include "../utils/ConsoleLog.h"
#include "../utils/FileLogger.h"
#include "../utils/Filesystem.h"
#include "../parsers/ServerConfig.h"
#include "../worldgen/WorldgenInit.h"
#include <boost/lexical_cast.hpp>
#include <boost/bind.hpp>


FileLogger *fileLogger;
std::shared_ptr<ServerAPI> serverAPI;


void ServerInit(int argc, char *argv[]){

    setlocale(LC_ALL,"");

    std::shared_ptr<ServerConfigParser> serverConfig(new ServerConfigParser( argc, argv));
    serverConfig->Parse();
    
    fileLogger = new FileLogger(serverConfig->data_dir);
    fileLogger->ErrorLog("Server Startup Initiated");
    fileLogger->ErrorLog("Server Configuration Read");
        
    DirectoryInit(serverConfig->data_dir);
    
    std::thread mysql( MySQLDBInit, serverConfig->db_hostname, serverConfig->db_port, serverConfig->db_username, serverConfig->db_pass, serverConfig->db_name );
    
    WorldGen *worldGen = new WorldGen(serverConfig);
    std::thread worldGenThread(&WorldGen::init, worldGen);
    
    mysql.join();
    worldGenThread.join();
    
    fileLogger->ErrorLog("Server Setup Complete");
            
    // After our startup threads are complete, we kickstart our game engines one at a time.
    // World Engine
    WorldEngine *worldEngine = new WorldEngine(worldGen->getWorldMap());
    std::thread worldEngineThread(&WorldEngine::init, worldEngine );
    
    // Physics Engine
    
    // AI Engine
    
    // Placeholder.
    
    
    // Break off our Net Initialization after everything is up and running.
    std::thread tcp_listener(NetInit, serverConfig->server_port);
    
    // We're on Our own now, Congratulations!
    // Our TCP Listener should be up soon too :-)
    fileLogger->ErrorLog("Server is Now Running, Congratulations!");

    tcp_listener.join();
    // Wait for our Shutdown before shutting down our engines.
    // Shutdown and join our engine threads backwards
    // Physics, AI, World
    
    worldEngineThread.join();
    
    return;    
}


void DirectoryInit(std::string rootFSPath){
    
    fileLogger->ErrorLog("Checking Filesystem Paths");
    
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
    
    fileLogger->ErrorLog("Filesystem Paths Verified");
    
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
        fileLogger->ErrorLog("Attempting to Start Network Module on Port: " + boost::lexical_cast<std::string>(port));
        boost::asio::io_service io_service;
        boost::asio::signal_set signals(io_service, SIGINT, SIGTERM);
        signals.async_wait(boost::bind(&boost::asio::io_service::stop, &io_service));
        tcp_handler_ptr tcp_server(new TCP_Handler(io_service, port));
        fileLogger->ErrorLog("Network Module Started and Listening on Port: " + boost::lexical_cast<std::string>(port));
        ConsoleLog::Print("Server is now Listening on Port: " + boost::lexical_cast<std::string>(port));
        io_service.run();
    }
    catch(std::exception& e){
        
        std::cerr << "Exception: " << e.what() << std::endl;
        
    }
    
}
