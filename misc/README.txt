This directory contains various 3rd party libraries that have been included in the project to ease development dependency setup time.

Please refer to the license files under the "licenses" directory for the legal information regarding these libraries.

NOTES (i.e. READ this before you attempt to compile these libs):

    As of 08/07/2012 the libpqxx libraries are having a few issues compiling properly under OSX/clang. I was able to get them compiled (using the tar.gz in this directory) by making the following changes:

        export CXX=clang++
        export CC=clang
        export CXFLAGS="-stdlib=libc++ -std=c++11"


    Under include/pqxx/util.hxx , you will need to make the following modifications:

        #ifdef PQXX_TR1_HEADERS
        #include <tr1/memory>
        #else
        #include <memory>
        #endif

    To:

        #ifdef PQXX_TR1_HEADERS
        #include <memory>
        #else
        #include <memory>
        #endif


    After these changes, you should be able to issue the following (your configure):

        ./configure --with-tr1=std


    If you continue to get errors, you may need to edit the top two lines in 
    include/pqxx/config-public-compiler.h file to the following:

        #define PGSTD std
        #define PQXXTR1 std




