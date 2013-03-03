#pragma once
//
//  TCP_Session.h
//  The ASCII Project
//
//  Created by Jonathan Rumion on 3/1/13.
//  Copyright (c) 2013 TAP. All rights reserved.
//

#include "TCP_Pool.h"
#include "Boost_Net_Asio.h"
#include "TCP_Participant.h"
#include <memory>

class TCP_Session : public TCP_Participant, public std::enable_shared_from_this<TCP_Session> {
    
private:
    
    boost::asio::ip::tcp::socket tcp_socket;
    TCP_Pool& tcp_pool;
    std::string clientIP;
    
    boost::asio::streambuf raw_line_command;

    
    
public:
    
    TCP_Session(boost::asio::io_service& io_service, TCP_Pool& pool) : tcp_socket(io_service), tcp_pool(pool){};

    boost::asio::ip::tcp::socket& socket(){return tcp_socket;}
    
    void start();
    void end();
    
    std::string getClientIP();
    
    // Our ASIO Functions
    void kickStart();
    void startSession(const boost::system::error_code& error);

};


typedef std::shared_ptr<TCP_Session> tcp_session_ptr;