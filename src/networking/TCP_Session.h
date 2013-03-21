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
#include "../utils/FileLogger.h"
#include <memory>
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>

#include <boost/tuple/tuple.hpp>
#include <iomanip>
#include <string>
#include <sstream>
#include <vector>

extern FileLogger *fileLogger;




class TCP_Session : public TCP_Participant, public boost::enable_shared_from_this<TCP_Session> {
    
private:
    
    boost::asio::ip::tcp::socket tcp_socket;
    boost::asio::io_service local_io_service;
    TCP_Pool& tcp_pool;
    std::string clientIP;
    
    boost::asio::streambuf raw_line_command;
    
    /// Holds an outbound header.
    std::string outbound_header_;
    
    /// Holds the outbound data.
    std::string outbound_data_;
    
    /// Holds an inbound header.
    char inbound_header_[HEADER_SIZE];
    
    /// Holds the inbound data.
    std::vector<char> inbound_data_;
    
    
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
    
    void startRaw();
    
    /// Asynchronously write a data structure to the socket.
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
        header_stream << std::setw(HEADER_SIZE) << std::hex << outbound_data_.size();
        if (!header_stream || header_stream.str().size() != HEADER_SIZE)
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
        boost::asio::async_write(this->tcp_socket, buffers, handler);
    }
    
    
    /// Asynchronously read a data structure from the socket.
    template <typename T, typename Handler>
    void async_read(const T& t, Handler handler)
    {
        // Issue a read operation to read exactly the number of bytes in a header.
        void (TCP_Session::*f)(const boost::system::error_code&, T&, boost::tuple<Handler>) = &TCP_Session::handle_read_header<T, Handler>;
        boost::asio::async_read(tcp_socket, boost::asio::buffer(inbound_header_), boost::bind(f, this, boost::asio::placeholders::error, boost::ref(t),
                                                                                              boost::make_tuple(handler)));
    }
    
    // Handle a completed read of a message header. The handler is passed using
    // a tuple since boost::bind seems to have trouble binding a function object
    // created using boost::bind as a parameter.
    template <typename T, typename Handler>
    void handle_read_header(const boost::system::error_code& e, T& t, boost::tuple<Handler> handler)
    {
        if (e)
        {
            boost::get<0>(handler)(e);
        }
        else
        {
            // Determine the length of the serialized data.
            std::istringstream is(std::string(inbound_header_, HEADER_SIZE));
            std::size_t inbound_data_size = 0;
            if (!(is >> std::hex >> inbound_data_size))
            {
                // Header doesn't seem to be valid. Inform the caller.
                boost::system::error_code error(boost::asio::error::invalid_argument);
                boost::get<0>(handler)(error);
                return;
            }
            
            // Start an asynchronous call to receive the data.
            inbound_data_.resize(inbound_data_size);
            void (TCP_Session::*f)(const boost::system::error_code&, T&, boost::tuple<Handler>) = &TCP_Session::handle_read_data<T, Handler>;
            boost::asio::async_read(tcp_socket, boost::asio::buffer(inbound_data_), boost::bind(f, this, boost::asio::placeholders::error, boost::ref(t), handler));
        }
    }
    
    
    // Handle a completed read of message data.
    template <typename T, typename Handler>
    void handle_read_data(const boost::system::error_code& e, T& t, boost::tuple<Handler> handler)
    {
        if (e)
        {
            boost::get<0>(handler)(e);
        }
        else
        {
            // Extract the data structure from the data just received.
            try
            {
                std::string archive_data(&inbound_data_[0], inbound_data_.size());
                std::istringstream archive_stream(archive_data);
                boost::archive::text_iarchive archive(archive_stream);
                archive >> t;
            }
            catch (std::exception& e)
            {
                // Unable to decode data.
                boost::system::error_code error(boost::asio::error::invalid_argument);
                boost::get<0>(handler)(error);
                return;
            }
            
            // Inform caller that data has been received ok.
            boost::get<0>(handler)(e);
        }
    }
    
};


typedef std::shared_ptr<TCP_Session> tcp_session_ptr;