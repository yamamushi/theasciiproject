//
//  TCP_Session.cpp
//  The ASCII Project
//
//  Created by Jonathan Rumion on 3/1/13.
//  Copyright (c) 2013 TAP. All rights reserved.
//

#include "Packets.h"
#include "TCP_Session.h"
#include "TCP_Participant.h"
#include "../api/ServerAPI.h"
#include "../utils/FileLogger.h"
#include "../serialization/Boost_Serialization.h"
#include <boost/bind.hpp>
#include <memory>
#include <iostream>
#include <vector>


// REMOVE THIS
#include "../mapping/WorldMap.h"
// REMOVE THIS



extern FileLogger *fileLogger;

void TCP_Session::start(){
    
    fileLogger->ErrorLog("Client " + getClientIP() + ": Connected");
    // Disable Nagles Algorithm - http://en.wikipedia.org/wiki/Nagle's_algorithm
    tcp_socket.set_option(boost::asio::ip::tcp::no_delay(true));
    // Join our tcp client pool
    tcp_pool.join(shared_from_this());
    
    kickStart();
}


/*
 
 Wrap all of our client cleanup into one function.
 
 */
void TCP_Session::end(){
    
    tcp_pool.leave(shared_from_this());
    fileLogger->ErrorLog("Client " + clientIP + ": Disconnected");
    
}



// Executed at TCP_Session::start()
std::string TCP_Session::getClientIP(){
    
    std::string remoteIP = tcp_socket.remote_endpoint().address().to_string();
    
    clientIP = remoteIP;
    return remoteIP;
    
}


// Start the async cycle
void TCP_Session::kickStart(){
    
    boost::asio::async_write(tcp_socket, boost::asio::buffer(std::string("Welcome to The ASCII Project\n\n"
                                                                         "Commands Available: \n"
                                                                         "------------------- \n\n"
                                                                         "term \n"
                                                                         "raw \n"
                                                                         "quit \r\n\r\n")),
                             boost::bind(&TCP_Session::startSession, shared_from_this(), boost::asio::placeholders::error ));
    
}


// Parse our Input
void TCP_Session::startSession(const boost::system::error_code& error)
{
    if (!error)
    {
        boost::asio::async_read_until(tcp_socket, raw_line_command, "\r\n", boost::bind(&TCP_Session::initMode, shared_from_this(),
                                                                                        boost::asio::placeholders::error ) );
    }
    else
    {
        end();
    }
}


void TCP_Session::initMode(const boost::system::error_code& error)
{
    if(!error)
    {
        std::string modeRequest;
        std::istream inputStream(&raw_line_command);
        
        inputStream >> modeRequest;
        
        fileLogger->ErrorLog("Client " + clientIP + ": INIT - " + modeRequest);
        
        if(modeRequest == "term")
        {
            end();
        }
        if(modeRequest == "raw")
        {
            
            /*
            HeaderPacket header;
            header.HeaderSize = (int)sizeof(HeaderPacket);
            
            std::ostringstream header_ofs;
            boost::archive::text_oarchive outputHeader(header_ofs);
            
            outputHeader << header;
            std::string outbound_header = header_ofs.str();
            
            std::vector<boost::asio::const_buffer> buffers;
            buffers.push_back(boost::asio::buffer(outbound_header)); */
            
            // Later on we'll pass this to a handler function that will accept an API request from a client
            //boost::asio::async_write( tcp_socket, boost::asio::buffer(""), boost::bind(&TCP_Session::end, shared_from_this() ) );
            startRaw();
            
        }
        else
        {
            end();
        }
        
    }
    else
    {
        end();
    }
}





void TCP_Session::sendHeader(const boost::system::error_code& error)
{
    if(!error)
    {
        HeaderPacket header;
        header.HeaderSize = (int)sizeof(HeaderPacket);
        
        std::ostringstream header_ofs;
        boost::archive::text_oarchive outputHeader(header_ofs);
        
        outputHeader << header;        
        std::string outbound_header = header_ofs.str();
        
        std::vector<boost::asio::const_buffer> buffers;
        buffers.push_back(boost::asio::buffer(outbound_header));
        
        boost::asio::async_write( tcp_socket, buffers, boost::bind(&TCP_Session::end, shared_from_this() ) );

    }
    else
    {
        end();
    }
}



void TCP_Session::startRaw(){
    
    std::shared_ptr<TileMap> rawTest_sharedptr(new TileMap(10, 10));
    TileMap *rawTest = rawTest_sharedptr.get();
    
    async_data_write(rawTest, boost::bind(&TCP_Session::end, shared_from_this()));
    
}
