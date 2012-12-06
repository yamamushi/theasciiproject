/*

  SelfPath - A simple function for retrieving the originating path of
  our executable (because of the whole, lets copy things into /proc on
  Linux ..)

*/

#include <string>
#include <unistd.h>


std::string SelfPath(){
  char buff[1024];
  ssize_t len = ::readlink("/proc/self/exe", buff, sizeof(buff)-1);
  if (len != -1) {
    buff[len] = '\0';
    return std::string(buff);
  } else {
    return std::string("nopathfound");
  }
}
