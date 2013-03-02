/*

  ServerInit
  Jonathan Rumion (Yamamushi)
  02-05-2013


  A wrapper function for basic server startup operations, directory
  checking, database checks, etc.

  Worldgen is kicked off from here, but its internals don't take place
  in this function.

 */

#include <string>

void ServerInit(int argc, char *argv[]);
void DirectoryInit(std::string rootFSPath);
void MySQLDBInit(std::string hostname, int port, std::string username, std::string pass, std::string database);

// 2-24-2013
/*
  Now we need to spin up and serialize-to-disk our map.
*/

void NetInit(int port);
