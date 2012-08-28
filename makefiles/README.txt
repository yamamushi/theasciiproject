DIRECTORY FOR MAKEFILES
=======================

MinGW Example:
--------------
Note: For more on building on Windows see: http://www.theasciiproject.com/wk/index.php/MinGW_Build

From the root director of the project (one directory down from here) type:

    make -f makefiles/makefile-mingw

To create a debug build (at least of the TheASCIIProject's code for now):

    make -f makefiles/makefile-mingw TAP_DEBUG=1

To create a profiler build:

    make -f makefiles/makefile-mingw TAP_PROFILE=1

Or even both:

    make -f makefiles/makefile-mingw TAP_DEBUG=1 TAP_PROFILE=1
    
TODO:
-----
-Include debug builds of dependency libraries with TAP_DEBUG=1
-Allow choosing static or dynamic linking to libc, libstdc++, and dependency libraries (eg. TAP_LINK_STATIC=1 TAP_LINK_DYNAMIC=1)