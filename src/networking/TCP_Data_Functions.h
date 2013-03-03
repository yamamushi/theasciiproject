#pragma once
//
//  TCP_Data_Functions.h
//  The ASCII Project
//
//  Created by Jonathan Rumion on 3/3/13.
//  Copyright (c) 2013 TAP. All rights reserved.
//

#include "Packets.h"
#include "../serialization/Boost_Serialization.h"

#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/tuple/tuple.hpp>
#include <iomanip>
#include <string>
#include <sstream>
#include <vector>

/*
/// Asynchronously read a data structure from the socket.
template <typename T, typename Handler>
void async_read(T& t, Handler handler)
{
    // Issue a read operation to read exactly the number of bytes in a header.
    void (connection::*f)(
                          const boost::system::error_code&,
                          T&, boost::tuple<Handler>)
    = &connection::handle_read_header<T, Handler>;
    boost::asio::async_read(socket_, boost::asio::buffer(inbound_header_),
                            boost::bind(f,
                                        this, boost::asio::placeholders::error, boost::ref(t),
                                        boost::make_tuple(handler)));
}

// Handle a completed read of a message header. The handler is passed using
// a tuple since boost::bind seems to have trouble binding a function object
// created using boost::bind as a parameter.
template <typename T, typename Handler>
void handle_read_header(const boost::system::error_code& e,
                        T& t, boost::tuple<Handler> handler)
{
    if (e)
    {
        boost::get<0>(handler)(e);
    }
    else
    {
        // Determine the length of the serialized data.
        std::istringstream is(std::string(inbound_header_, header_length));
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
        void (connection::*f)(
                              const boost::system::error_code&,
                              T&, boost::tuple<Handler>)
        = &connection::handle_read_data<T, Handler>;
        boost::asio::async_read(socket_, boost::asio::buffer(inbound_data_),
                                boost::bind(f, this,
                                            boost::asio::placeholders::error, boost::ref(t), handler));
    }
}

/// Handle a completed read of message data.
template <typename T, typename Handler>
void handle_read_data(const boost::system::error_code& e,
                      T& t, boost::tuple<Handler> handler)
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
*/