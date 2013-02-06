/*

  ServerInit

  Jonathan Rumion (Yamamushi)
  02-05-2013
  

 */


#include "ServerInit.h"

#include "../utils/ConsoleLog.h"
#include "../utils/Filesystem.h"
#include "../parsers/ServerConfig.h"

void ServerInit(int argc, char *argv[]){

  ServerConfigParser *serverConfig = new ServerConfigParser( argc, argv);
  serverConfig->Parse();

  FileSystem::MkDir(serverConfig->data_dir);

  return;

};
