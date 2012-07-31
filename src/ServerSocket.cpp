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

typedef boost::shared_ptr<client_connection> pointer;
typedef boost::shared_ptr<client_participant> client_participant_ptr;
typedef boost::shared_ptr<client_connection> client_connection_ptr;



void client_pool::join(client_participant_ptr client)
{
    clients_.insert(client);
    
}


void client_pool::leave(client_participant_ptr client)
{
    clients_.erase(client);
}


void client_pool::deliver()
{
    
    std::for_each(clients_.begin(), clients_.end(), boost::bind(&client_participant::updatePlayerMap, _1));
    
}





tcp::socket& client_connection::socket()
{
    return socket_;
}


void client_connection::start()
{
    len = 0;
    sent = 0;
    stream = new char[1];
    client_pool_.join(shared_from_this());
    mapBuf = new vector<char *>;
    sync();
    
}


void client_connection::sync()
{
    
    
    int x = atoi(&tmp);
    
    if(x != 0)
    {
        handleAPI(x);
        updatePlayerMap();
        
    }
    
    if(sent >= len)
    {
        updatePlayerMap();
    }
    
    
    boost::asio::async_write(socket_, boost::asio::buffer(stream + sent, 4096), boost::bind(&client_connection::handle_write, shared_from_this(), boost::asio::placeholders::bytes_transferred, boost::asio::placeholders::error));
    
    
}





void client_connection::handle_write(size_t bytes, const boost::system::error_code& error)
{
    if (!error)
    {
        sent = sent + 4096;
        boost::asio::async_read(socket_, boost::asio::buffer(&tmp, 1), boost::bind(&client_connection::sync, shared_from_this()));
    }
    else{
        free(stream);
        client_pool_.leave(shared_from_this());
    }
    
}


void client_connection::updatePlayerMap()
{
    sent = 0;
    
   // delete mapBuf;
   // mapBuf = new vector<char *>;
    
    
    free(stream);
    
    extern Entity *test;
    
    renderForPlayer(test, mapBuf);
    
    len = mapBuf->size()*128;
    
    
    stream = new char[len];
    memset(stream, '0', len);
    
    for(int x = 0; x < mapBuf->size(); x++)
    {
        memcpy(stream + (x*128), mapBuf->back(), 128);
        stream[(x+1) * (128)] = '\n';
        free(mapBuf->back());
        mapBuf->pop_back();
    }

    
}




void client_connection::handleAPI(int api)
{
    extern Entity *test;
    
    // We start off by mapping our numpad keys
    // To movement directions
    
    if ( api == 1)
    {
        test->move(-1, 1);
    }
    if ( api == 2)
    {
        test->move(0, 1);
    }
    if ( api == 3)
    {
        test->move(1, 1);
    }
    if (api == 4)
    {
        test->move(-1, 0);
    }
    if (api == 5)
    {
        test->move(0, 0);
    }
    if (api == 6)
    {
        test->move(1, 0);
    }
    if (api == 7)
    {
        test->move(-1, -1);
    }
    if (api == 8)
    {
        test->move(0, -1);
    }
    if (api == 9)
    {
        test->move(1, -1);
    }
    
}







game_server::game_server(boost::asio::io_service& io_service, const tcp::endpoint& endpoint)
: io_service_(io_service), acceptor_(io_service, endpoint)
{
    start_accept();
}


void game_server::start_accept()
{
    client_connection_ptr new_session(new client_connection(io_service_, client_pool_));
    
    acceptor_.async_accept(new_session->socket(), boost::bind(&game_server::handle_accept, this, new_session, boost::asio::placeholders::error));
}

void game_server::handle_accept(client_connection_ptr client, const boost::system::error_code& error)
{
    if (!error)
    {
        client->start();
    }
    
    start_accept();
}
































