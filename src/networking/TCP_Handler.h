#pragma once
//
//  TCP_Handler.h
//  The ASCII Project
//
//  Created by Jonathan Rumion on 3/1/13.
//  Copyright (c) 2013 TAP. All rights reserved.
//

#include "TCP_Session.h"
#include "TCP_Pool.h"

#include "Boost_Net_Asio.h"
#include <memory>


class TCP_Handler {
    
private:
    
    boost::asio::io_service& tcp_io_service;
    boost::asio::ip::tcp::acceptor tcp_acceptor;
    
    TCP_Pool tcp_pool;
    
    
    
public:
    
    TCP_Handler(boost::asio::io_service& io_service, int port) : tcp_io_service(io_service), tcp_acceptor(io_service, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port)) {
        accept_connection();
    }
    
    
    void accept_connection();
    void handle_connection(tcp_session_ptr tcp_session, const boost::system::error_code& error);
    
};

typedef std::shared_ptr<TCP_Handler> tcp_handler_ptr;