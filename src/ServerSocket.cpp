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

//#include <pqxx/pqxx> /* Moved from Headers.h */
#include "DBConnector.h" /* Moved from Headers.h */

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
    maxsent = 0;
    
    line_command_ = new boost::asio::streambuf;
    
    client_pool_.join(shared_from_this());
    
    mapBuf = new vector<char *>;
    mapSize = new char[16];
    
    cmd = new char[2];
    cmd[0] = '\r';
    cmd[1] = '\n';
    stream = new char[MAX_PACKET_SIZE];
    memset(stream, '.', MAX_PACKET_SIZE);
    updatePlayerMap();
    
    kickStart();
}




void client_connection::kickStart()
{
    
    boost::asio::async_write(socket_, boost::asio::buffer(string("Welcome to The ASCII Project Public Server\r\n\r\n"
                                                                 "Commands Available:\r\n"
                                                                 "-------------------\n\n"
                                                                 "login: user pass\r\n"
                                                                 "newaccount: user pass\r\n"
                                                                 "quit\r\n\r\n"
                                                                 "ascii=> ")), boost::bind(&client_connection::startSession, shared_from_this(), boost::asio::placeholders::error ));
    
}



void client_connection::startSession(const boost::system::error_code& error)
{
    if (!error)
    {
        boost::asio::async_read_until(socket_, *line_command_, "\r\n", boost::bind(&client_connection::sessionStartHandler, shared_from_this(), boost::asio::placeholders::error ));
    }
    else
    {
        disconnect();
    }
}


void client_connection::sessionStartHandler(const boost::system::error_code& error)
{
    if (!error)
    {
        std::string command;
        
        std::istream is(line_command_);
        is >> command;
        
        delete line_command_;
        line_command_ = new boost::asio::streambuf;
        
        if(command == "login" || command == "Login")
        {
            boost::asio::async_read_until(socket_, *line_command_, "\r\n", boost::bind(&client_connection::login, shared_from_this(), boost::asio::placeholders::error ));
        }
        else if(command == "newAccount" || command == "newUser" || command == "newaccount" || command == "newuser")
        {
            boost::asio::async_read_until(socket_, *line_command_, "\r\n", boost::bind(&client_connection::createAccount, shared_from_this(), boost::asio::placeholders::error ));
        }
        else if(command == "quit")
        {
            disconnect();
        }
        else
        {
            boost::asio::async_write(socket_, boost::asio::buffer(string("ascii=> ")), boost::bind(&client_connection::startSession, shared_from_this(), boost::asio::placeholders::error ));
        }
        
    }
    else
    {
        disconnect();
    }
}


void client_connection::login(const boost::system::error_code& error)
{
    if (!error)
    {
      
        std::istream is(line_command_);
        is >> user >> pass;
        
        delete line_command_;
        line_command_ = new boost::asio::streambuf;
        
        cout << "Received Connect Attempt: User - " << user << " :: pass - " << pass << endl;
        
        if( user.compare("") == 0)
        {
            boost::asio::async_read_until(socket_, *line_command_, "\r\n", boost::bind(&client_connection::login, shared_from_this(), boost::asio::placeholders::error ));
        }
        else
        {
            extern DBConnector *dbEngine;
            
            if(!dbEngine->isValidHash((const std::string)user, (const std::string)pass))
            {
                
                boost::asio::async_write(socket_, boost::asio::buffer(string("Invalid Username or Password - Syntax(username password)\r\nascii=> ")), boost::bind(&client_connection::startSession, shared_from_this(), boost::asio::placeholders::error ));
            }
            else
            {
                sessionToken = dbEngine->GenerateToken(user, pass);
                boost::asio::async_write(socket_, boost::asio::buffer(string("Welcome to The ASCII Project " + user + "\r\n" + sessionToken + "\r\nascii=> ")), boost::bind(&client_connection::receive_command, shared_from_this(), boost::asio::placeholders::error ));
            }
        }
        
    }
    else
    {
        disconnect();
    }
    
}

void client_connection::createAccount(const boost::system::error_code& error)
{
    if (!error)
    {
        
        std::istream is(line_command_);
        is >> user >> pass;
        
        if( user.compare("") == 0 || pass.compare("") == 0)
        {
            boost::asio::async_write(socket_, boost::asio::buffer(string("New Account Syntax(username password)r\nascii=> ")), boost::bind(&client_connection::startSession, shared_from_this(), boost::asio::placeholders::error ));
        }
        else
        {
            extern DBConnector *dbEngine;
            dbEngine->AddAccount(user, pass);
            boost::asio::async_write(socket_, boost::asio::buffer(string("Account Created, you may now login\r\nascii=> ")), boost::bind(&client_connection::startSession, shared_from_this(), boost::asio::placeholders::error ));
            
        }
        
        
    }
    else
    {
        disconnect();
    }
}



void client_connection::receive_command(const boost::system::error_code& error)
{
    if (!error)
    {
        sessionToken = "";
        boost::asio::async_read_until(socket_, *line_command_, "\r\n", boost::bind(&client_connection::handle_request_line, shared_from_this(), boost::asio::placeholders::error ));
    }
    else
    {
        disconnect();
    }
    
}


void client_connection::handle_request_line(const boost::system::error_code& error)
{
    if (!error)
    {
        extern DBConnector *dbEngine;
        
        std::string command, token;
        
        std::istream is(line_command_);
        is >> command >> token ;
        
        delete line_command_;
        line_command_ = new boost::asio::streambuf;
        
        
        if(isInteger(command))
        {
            if(dbEngine->isValidToken( user, token))
            {
                handleAPI(atoi(command.c_str()));
                boost::asio::async_write(socket_, boost::asio::buffer(string("ascii=> ")), boost::bind(&client_connection::receive_command, shared_from_this(), boost::asio::placeholders::error ));
            }
            else
            {
                disconnect();
            }
        }
        else if( command == "startMapStream")
        {
            if(dbEngine->isValidToken( user, token))
            {
                
                updatePlayerMap();
                free(mapSize);
                mapSize = new char[16];
                
                memset(mapSize, '\0', 16);
                
                sprintf(mapSize, "%d", (int)len);
                
                // int x = atoi(mapSize);
                //  printf("map is %d\n", x);
                
                boost::asio::async_write(socket_, boost::asio::buffer(&mapSize[0], 16), boost::bind(&client_connection::clientAcceptMapSize, shared_from_this(), boost::asio::placeholders::error));
            }
            else
            {
                disconnect();
            }
            
            
        }
        else if( command == "quit")
        {
            
            disconnect();
            
        }
        else if( command == "time")
        {
            time_t rawtime;
            
            struct tm * timeinfo;
            time( &rawtime );
            timeinfo = localtime(&rawtime);
            
            string time = asctime(timeinfo);
            
            boost::asio::async_write(socket_, boost::asio::buffer(time), boost::bind(&client_connection::receive_command, shared_from_this(), boost::asio::placeholders::error ));
        }
        else if( command == "" )
        {
            boost::asio::async_write(socket_, boost::asio::buffer(string("ascii=> ")), boost::bind(&client_connection::receive_command, shared_from_this(), boost::asio::placeholders::error ));
        }
        else
        {
            boost::asio::async_read_until(socket_, *line_command_, "\r\n", boost::bind(&client_connection::receive_command, shared_from_this(), boost::asio::placeholders::error ));
        }
        
    }
    
    else
    {
        disconnect();
    }
}


void client_connection::clientAcceptMapSize(const boost::system::error_code& error)
{
    if(!error)
    {
        boost::asio::async_read(socket_, boost::asio::buffer(&cmd[0], 1), boost::bind(&client_connection::sendMap, shared_from_this(), boost::asio::placeholders::error));
        
    }
    else
    {
        disconnect();
    }
}




void client_connection::sendMap(const boost::system::error_code& error)
{
    if(!error)
    {
        boost::asio::async_write(socket_, boost::asio::buffer(stream, len), boost::bind(&client_connection::receive_command, shared_from_this(), boost::asio::placeholders::error));
    }
    else
    {
        disconnect();
        
    }
    
    
}








void client_connection::sync()
{
    
    int x = atoi(&cmd[0]);
    
    if(x >= 0)
    {
        handleAPI(x);
        updatePlayerMap();
    }
    
    
    if(sent > 0)
    {
        memset(stream, '.', sent);
    }
    
    
    boost::asio::async_write(socket_, boost::asio::buffer(stream + sent, len), boost::bind(&client_connection::handle_write, shared_from_this(), boost::asio::placeholders::bytes_transferred, boost::asio::placeholders::error));
    
}





void client_connection::handle_write(size_t bytes, const boost::system::error_code& error)
{
    if (!error)
    {
        sent += len;
        
        if(sent > maxsent)
        {
            maxsent = sent;
        }
        
        boost::asio::async_read(socket_, boost::asio::buffer(cmd, 2), boost::bind(&client_connection::sync, shared_from_this()));
    }
    
    else{
        
        disconnect();
    }
    
}





void client_connection::updatePlayerMap()
{
    sent = 0;
    
    extern Entity *test;
    
    mapBuf->clear();
    renderForPlayer(test, mapBuf);
    
    
    len = ((mapBuf->size())*TILE_PACKET_SIZE);
    
    if(len > MAX_PACKET_SIZE)
    {
        len = MAX_PACKET_SIZE;
        mapBuf->resize(MAX_VECTOR_BUFFER);
    }
    
    
    free(stream);
    
    
    stream = new char[len];
    
    memset(stream, '.', len);
    
    memcpy(stream, mapBuf->at(0), TILE_PACKET_SIZE);
    free(mapBuf->at(0));
    
    for(int x = 1; x < mapBuf->size(); x++)
    {
        memcpy(stream + ((x*(TILE_PACKET_SIZE) - 1)), mapBuf->at(x), TILE_PACKET_SIZE);
        free(mapBuf->at(x));
        
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
    else if ( api == 2)
    {
        test->move(0, 1);
    }
    else if ( api == 3)
    {
        test->move(1, 1);
    }
    else if (api == 4)
    {
        test->move(-1, 0);
    }
    else if (api == 5)
    {
        test->move(0, 0);
    }
    else if (api == 6)
    {
        test->move(1, 0);
    }
    else if (api == 7)
    {
        test->move(-1, -1);
    }
    else if (api == 8)
    {
        test->move(0, -1);
    }
    else if (api == 9)
    {
        test->move(1, -1);
    }
    else
    {
        test->move(0, 0);
    }
    
}




void client_connection::disconnect()
{
    
    
    free(stream);
    free(mapSize);
    
    delete mapBuf;
    client_pool_.leave(shared_from_this());
    
    
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
































