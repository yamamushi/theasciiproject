//
//  main.cpp
//  Server
//
//  Created by Jonathan Rumion on 10/8/12.
//  Copyright (c) 2012 Jonathan Rumion. All rights reserved.
//

#include <iostream>
#include "BoostLibs.h"
#include "ServerSocket.h"





using namespace std;

int main(int argc, const char * argv[])
{

    cout << "Testing Boost ASIO" << endl;
    setlocale(LC_ALL, "");
    
    try
    {
        boost::asio::io_service io_service;
        tcp::endpoint endpoint(tcp::v4(), 5250);
        boost::asio::signal_set signals(io_service, SIGINT, SIGTERM);
        signals.async_wait(boost::bind(&boost::asio::io_service::stop, &io_service));
        game_server server(io_service, endpoint);
        io_service.run();
    }
    catch (std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }

    
    return 0;
}

