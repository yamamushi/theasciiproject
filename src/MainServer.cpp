/*

  The ASCII Project - Server

  0.0.1f - December 5th, 2012 

  http://www.theasciiproject.com
  Jonathan Rumion - yamamushi@gmail.com

 */

#include "server/ServerInit.h"


int main(int argc, char *argv[]){

  // We can forego these console messages, as our config parser will
  // do that for us.

  // ConsoleLog::Print("The ASCII Project");
  // ConsoleLog::Print("Reading configuration file...");

  ServerInit(argc, argv);
  
  return 0;

}

