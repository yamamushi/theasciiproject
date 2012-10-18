/*
 * =====================================================================================
 *
 *       Filename:  ServerSocket.h
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


#ifndef The_ASCII_Project_ServerSocket_h
#define The_ASCII_Project_ServerSocket_h

#include "BoostLibs.h"
#include "Constants.h"
#include "UnicodeConstants.h"
#include "Display.h"
#include "Keyboard.h"



class ClientMapPacker;


class client_participant
{
public:
    virtual ~client_participant() {}
 //   virtual void sync() = 0;
 //   virtual void updatePlayerMap() = 0;
 //   virtual void addToChatStream(std::string message) = 0;
};

typedef boost::shared_ptr<client_participant> client_participant_ptr;




class client_pool
{
private:
    std::set<client_participant_ptr> clients_;
    
public:
    void join(client_participant_ptr client);
    void leave(client_participant_ptr client);
    void deliver(std::string message);

};





class client_connection : public client_participant, public boost::enable_shared_from_this<client_connection>
{
    
private:
    
    int failedConnects;
    int sent;
    int maxsent;
    
    
    char *stream;
    char *cmd;
    char *mapSize;
    char headerSize[2];
    
    std::vector<char *> *mapBuf;
    
    Display *display;
    Keyboard *keyboard;
    
   
    tcp::socket socket_;
    client_pool& client_pool_;

    
    boost::asio::streambuf *line_command_;

        
public:
    
    
    client_connection(boost::asio::io_service& io_service, client_pool& pool) : socket_(io_service), client_pool_(pool) {};
    
    tcp::socket& socket();
   
    
    void start();    
    void kickStart();
    
    void startSession(const boost::system::error_code& error);     
    void receive_command(const boost::system::error_code& error);    
    void handle_request_line(const boost::system::error_code& error);
    
    void disconnect();
    

};






typedef boost::shared_ptr<client_connection> client_connection_ptr;


class game_server
{
    
private:
    boost::asio::io_service& io_service_;
    tcp::acceptor acceptor_;
    client_pool client_pool_;
    
    
public:
    game_server(boost::asio::io_service& io_service, const tcp::endpoint& endpoint);
    
    void start_accept();
    void handle_accept(client_connection_ptr client, const boost::system::error_code& error);
    
};




#endif
