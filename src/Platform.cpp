/*
 *  Filename: platform.cpp
 *  Comments:
 *    Defines functions that are to be used on specific platforms.
 */

#ifdef __APPLE__
#include "CoreFoundation/CoreFoundation.h"
#include <iostream>
#endif

// ----------------------------------------------------------------------------
// This makes relative paths work in C++ in Xcode by changing directory to the
// Resources folder inside the .app bundle
#ifdef __APPLE__
void macApp_setRelativePath() {
    CFBundleRef mainBundle = CFBundleGetMainBundle();
    CFURLRef resourcesURL = CFBundleCopyResourcesDirectoryURL(mainBundle);
    char path[PATH_MAX];
    if (!CFURLGetFileSystemRepresentation(resourcesURL, TRUE, (UInt8 *)path, PATH_MAX))
    {
        // error!
    }
    CFRelease(resourcesURL);
    
    chdir(path);
    std::cout << "[Mac] Set path to " << path << std::endl;
}
#endif
// ----------------------------------------------------------------------------