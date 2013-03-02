//
//  TCP_Handler.cpp
//  The ASCII Project
//
//  Created by Jonathan Rumion on 3/1/13.
//  Copyright (c) 2013 TAP. All rights reserved.
//

#include "TCP_Handler.h"
#include "Boost_Net_Asio.h"
#include "TCP_Session.h"
#include <boost/bind.hpp>
#include <memory>


void TCP_Handler::accept_connection(){
    
    tcp_session_ptr new_tcp_session(new TCP_Session(tcp_io_service, tcp_pool));
    
    // It's important to remember this is an async_accept, not a plain ol' accept :-)
    tcp_acceptor.async_accept(new_tcp_session->socket(), boost::bind(&TCP_Handler::handle_connection, this, new_tcp_session, boost::asio::placeholders::error));
    
}

void TCP_Handler::handle_connection(tcp_session_ptr tcp_session, const boost::system::error_code& error){
    
    if(!error){
        tcp_session->start();
    }
    
    accept_connection();
    
}



