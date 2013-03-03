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
#include "Packets.h"
#include "../serialization/Boost_Serialization.h"
#include <memory>
#include <boost/bind.hpp>

class TCP_Session : public TCP_Participant, public std::enable_shared_from_this<TCP_Session> {
    
private:
    
    boost::asio::ip::tcp::socket tcp_socket;
    boost::asio::io_service local_io_service;
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
    void initMode(const boost::system::error_code& error);

    
    void sendHeader(const boost::system::error_code& error);
    
    /// Asynchronously write a data structure to the socket.
    
    // I have to fix this, this doesn't mix well with our
    // Data structures, but I anticipate it's a "simple" fix.
    template <typename T, typename Handler>
    void async_data_write(const T& t, Handler handler)
    {
        // Serialize the data first so we know how large it is.
        std::ostringstream archive_stream;
        boost::archive::text_oarchive archive(archive_stream);
        archive << t;
        std::string outbound_data_ = archive_stream.str();
        
        // Format the header.
        std::ostringstream header_stream;
        header_stream << std::setw(header_length)
        << std::hex << outbound_data_.size();
        if (!header_stream || header_stream.str().size() != header_length)
        {
            // Something went wrong, inform the caller.
            boost::system::error_code error(boost::asio::error::invalid_argument);
            //socket().post(boost::bind(handler, error));
            end();
            return;
        }
        std::string outbound_header_ = header_stream.str();
        
        // Write the serialized data to the socket. We use "gather-write" to send
        // both the header and the data in a single write operation.
        std::vector<boost::asio::const_buffer> buffers;
        buffers.push_back(boost::asio::buffer(outbound_header_));
        buffers.push_back(boost::asio::buffer(outbound_data_));
        boost::asio::async_write(tcp_socket, buffers, handler);
    }

};


typedef std::shared_ptr<TCP_Session> tcp_session_ptr;