/*
 
 Filesystem
 
 A wrapper over boost::filesystem for creating directories
 
 Jonathan Rumion (Yamamushi)
 02-05-2013
 
 */
#include <string>


class FileSystem {
    
private:
    
public:
    
    FileSystem();
    virtual ~FileSystem(){};
    
    // We can keep these functions similar to unix commands, for my own
    // sanity.
    static void MkDir(std::string path);
    static bool CheckExists(std::string path);
    
};
