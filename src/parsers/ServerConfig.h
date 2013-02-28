#pragma once
/*

  Server Configuration parser

*/

#include <boost/program_options.hpp>
#include <string>

namespace po = boost::program_options;

class ServerConfigParser {

private:

  int argc;
  char** argv;


public:
  
  ServerConfigParser(int argc_, char** argv_);
  virtual ~ServerConfigParser(){};
  
  // This will kick off the parse operation
  void Parse();
  
  // We'll make this simple and list our program options here
  // Which allows us to quickly retrieve them from other parts
  // Of runtime.

  std::string config_file;
  
  // Filesystem Path
  // ie, data_dir + "/maps"
  std::string data_dir;

  // DB Options
  std::string db_hostname;
  int db_port;
  std::string db_username;
  std::string db_pass;
  std::string db_name;

  // Server Bind Options
  int server_port;

  // WorldGen Parameters <- this will be changed later.
  int mapX;
  int mapY;
  int worldX;
  int worldY;
  int worldZ;

};
