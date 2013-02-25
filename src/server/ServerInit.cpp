/*

  ServerInit

  Jonathan Rumion (Yamamushi)
  02-05-2013
  

 */

#include <string>
#include <iostream>

#include "ServerInit.h"
#include "../db/MySQLServerDB.h"
#include "../utils/ConsoleLog.h"
#include "../utils/FileLogger.h"
#include "../utils/Filesystem.h"
#include "../parsers/ServerConfig.h"


FileLogger *fileLogger;



void ServerInit(int argc, char *argv[]){

  ServerConfigParser *serverConfig = new ServerConfigParser( argc, argv);
  serverConfig->Parse();

  DirectoryInit(serverConfig->data_dir);
  
  fileLogger = new FileLogger(serverConfig->data_dir);
  fileLogger->ErrorLog("Server Configuration Read");

  MySQLDBInit(serverConfig->db_hostname, serverConfig->db_port, serverConfig->db_username, serverConfig->db_pass, serverConfig->db_name);
  
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
