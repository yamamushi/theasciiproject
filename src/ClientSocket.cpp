/*
 * =====================================================================================
 *
 *       Filename:  ClientSocket.cpp
 *
 *    Description:  Wrapper for Boost::Asio library as used in the Client.
 *
 *        Version:  1.0
 *        Created:  07/20/2012 10:28 PM
 *       Revision:  Rev 1 - 07/26/2012
 *       Compiler:  clang++
 *
 *         Author:  Yamamushi (Jon Rumion)
 *   Organization:  The ASCII Project
 *
 *	  License:  GPLv3
 *
 *	  Copyright 2012 Jonathan Rumion
 *
 *   This file is part of The ASCII Project.
 *
 *   The ASCII Project is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.
 *
 *   The ASCII Project is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with The ASCII Project.  If not, see <http://www.gnu.org/licenses/>.
 *
 *
 * =====================================================================================
 */

#include "Headers.h"


using boost::asio::ip::tcp;


ClientSession::ClientSession(boost::asio::io_service& io_service, tcp::resolver::iterator endpoint_iterator) : io_service_(io_service), socket_(io_service)
{
    boost::asio::async_connect(socket_, endpoint_iterator, boost::bind(&ClientSession::handle_connect, this, boost::asio::placeholders::error));
}

void ClientSession::handle_connect(const boost::system::error_code& error)
{
    if (!error)
    {
        cout << "Connected\n";
    }
    else
    {
        close();
    }
}

void ClientSession::read_map(ClientMap *client, ClientMapPacker *pEngine)
{
    
    //client->cleanMap();
    
    for (int x = 0; x < 64; x++)
    {
        boost::array<char, 128> buf;
        //char *buf = new char[128];
        
        //boost::asio::async_read(socket_, boost::asio::buffer(buf, 128), boost::bind(&ClientSession::handle_connect, this, boost::asio::placeholders::error));
        socket_.receive(boost::asio::buffer(buf));
        boost::asio::const_buffer b1 = boost::asio::buffer(buf);
        const unsigned char* p1 = boost::asio::buffer_cast<const unsigned char*>(b1);
        pEngine->unpackFromNet(client, (unsigned char*)p1);
    }
    
}

void ClientSession::close()
{
    io_service_.post(boost::bind(&ClientSession::do_close, this));
}

void ClientSession::do_close()
{
    socket_.close();
}




















