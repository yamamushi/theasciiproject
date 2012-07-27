/*
 * =====================================================================================
 *
 *       Filename:  ServerSocket.cpp
 *
 *    Description:  Experimental Sockets Implementation
 *
 *        Version:  1.0
 *        Created:  07/20/2012 08:38 PM
 *       Revision:  none
 *       Compiler:  gcc
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
#include "ServerSocket.h"

typedef boost::shared_ptr<tcp_connection> pointer;



pointer tcp_connection::create(boost::asio::io_service& io_service)
{
    return pointer(new tcp_connection(io_service));
}

tcp::socket& tcp_connection::socket()
{
    return socket_;
}

void tcp_connection::start()
{
    //message_ = make_daytime_string();
    extern Entity *test;
    cout << "Entity pointer defined\n";
    
    cout << "Vector assigned\n";
    
    vector<char *> *mapBuf = new vector<char *>;
    renderForPlayer(test, mapBuf);
    
    //socket_.send( boost::asio::buffer(*mapBuf), boost::bind(&tcp_connection::handle_write, shared_from_this()));
    //const char * px = reinterpret_cast<const char*>(&mapBuf);
    
    for (int x=0; x < mapBuf->size(); x++)
    {
    boost::asio::async_write(socket_, boost::asio::buffer(mapBuf->at(x), 128),
                             boost::bind(&tcp_connection::handle_write, shared_from_this(), boost::asio::placeholders::bytes_transferred));
    }
    
    
}


void tcp_connection::handle_write(size_t bytes)
{
    cout << bytes << ": bytes sent\n";
}



tcp_server::tcp_server(boost::asio::io_service& io_service)
: acceptor_(io_service, tcp::endpoint(tcp::v4(), 5250))
{
    start_accept();
}


void tcp_server::start_accept()
{
    tcp_connection::pointer new_connection = tcp_connection::create(acceptor_.get_io_service());
    
    acceptor_.async_accept(new_connection->socket(),
                           boost::bind(&tcp_server::handle_accept, this, new_connection,
                                       boost::asio::placeholders::error));
}

void tcp_server::handle_accept(tcp_connection::pointer new_connection, const boost::system::error_code& error)
{
    if (!error)
    {
        new_connection->start();
    }
    
    start_accept();
}


















