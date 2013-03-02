//
//  TCP_Session.cpp
//  The ASCII Project
//
//  Created by Jonathan Rumion on 3/1/13.
//  Copyright (c) 2013 TAP. All rights reserved.
//

#include "TCP_Session.h"
#include "TCP_Participant.h"
#include <boost/bind.hpp>
#include <memory>
#include <iostream>

void TCP_Session::start(){
    
    tcp_pool.join(shared_from_this());
    
    std::cout << "Client Connected" << std::endl;
    
}


void TCP_Session::end(){
    
    tcp_pool.leave(shared_from_this());
    std::cout << "Client Disconnected" << std::endl;
    
}