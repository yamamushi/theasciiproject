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

  if(!FileSystem::CheckExists(serverConfig->data_dir)){
    FileSystem::MkDir(serverConfig->data_dir);
  }
  if(!FileSystem::CheckExists(serverConfig->data_dir + "/ents")){
    FileSystem::MkDir(serverConfig->data_dir + "/ents");
  }
  if(!FileSystem::CheckExists(serverConfig->data_dir + "/logs")){
    FileSystem::MkDir(serverConfig->data_dir + "/logs");
  }
  if(!FileSystem::CheckExists(serverConfig->data_dir + "/maps")){
    FileSystem::MkDir(serverConfig->data_dir + "/maps");
  }
  if(!FileSystem::CheckExists(serverConfig->data_dir + "/players")){
    FileSystem::MkDir(serverConfig->data_dir + "/players");
  }
  if(!FileSystem::CheckExists(serverConfig->data_dir + "/scripts")){
    FileSystem::MkDir(serverConfig->data_dir + "/scripts");
  }

  return;

}
