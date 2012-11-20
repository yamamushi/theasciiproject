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



#include <vector>
#include <iostream>
#include <fstream>
#include "DBConnector.h"

#include "ClientMap.h"
#include "ServerSocket.h"
#include "WorldMap.h"
#include "Collect.h"
#include "TileMap.h"
#include "InputParser.h"

using std::vector;
using std::string;
using std::cout;
using std::endl;

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


void client_pool::deliver(std::string message)
{
    std::for_each(clients_.begin(), clients_.end(), boost::bind(&client_participant::addToChatStream, _1, message));
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
    
    forceReset = false;
    
    username_feed_ = new boost::asio::streambuf;
    pass_feed_ = new boost::asio::streambuf;
    
    line_command_ = new boost::asio::streambuf;
    chat_message_ = new boost::asio::streambuf;
    
    client_pool_.join(shared_from_this());
    
    mapBuf = new vector<char *>;
    mapSize = new char[16];
    savedMap = new ClientMap();
    
    player = nullptr;
    
    cmd = new char[2];
    cmd[0] = '\r';
    cmd[1] = '\n';
    stream = new char[MAX_PACKET_SIZE];
    memset(stream, '.', MAX_PACKET_SIZE);
        
    kickStart();
}



void client_connection::addToChatStream(std::string message)
{
    
    chatStream.append(message);    
    
    
}




void client_connection::kickStart()
{
    socket_.set_option(tcp::no_delay(true));

    boost::asio::async_write(socket_, boost::asio::buffer(string("Welcome to The ASCII Project\n\n"
                                                                 "Commands Available: \n"
                                                                 "------------------- \n\n"
                                                                 "login\n"
                                                                 "newaccount\n"
                                                                 "quit \r\n\r\n")), boost::bind(&client_connection::startSession, shared_from_this(), boost::asio::placeholders::error ));
    
}



void client_connection::startSession(const boost::system::error_code& error)
{
    if (!error)
    {
        
        delete line_command_;
        line_command_ = new boost::asio::streambuf;
        
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
        std::string command, garbage;
        
        std::istream is(line_command_);
        is >> command >> garbage;
        
        delete line_command_;
        line_command_ = new boost::asio::streambuf;
        
        if(command == "login" || command == "Login")
        {
            //boost::asio::async_read_until(socket_, *line_command_, "\r\n", boost::bind(&client_connection::login, shared_from_this(), boost::asio::placeholders::error ));
            boost::asio::async_write(socket_, boost::asio::buffer(string("Username: \r\n\r\n")), boost::bind(&client_connection::loginGetUser, shared_from_this(), boost::asio::placeholders::error ));
        }
        else if(command == "newAccount" || command == "newUser" || command == "newaccount" || command == "newuser")
        {
            //boost::asio::async_read_until(socket_, *line_command_, "\r\n", boost::bind(&client_connection::createAccount, shared_from_this(), boost::asio::placeholders::error ));
            boost::asio::async_write(socket_, boost::asio::buffer(string("Username: \r\n\r\n")), boost::bind(&client_connection::newAccountGetUser, shared_from_this(), boost::asio::placeholders::error ));
            
        }
        else if(command == "quit")
        {
            disconnect();
        }
        else
        {
            boost::asio::async_write(socket_, boost::asio::buffer(string(" \r\n\r\n")), boost::bind(&client_connection::startSession, shared_from_this(), boost::asio::placeholders::error ));
        }
        
    }
    else
    {
        disconnect();
    }
}



void client_connection::loginGetUser(const boost::system::error_code& error)
{
    if(!error)
    {
        boost::asio::async_read_until(socket_, *username_feed_, "\r\n", boost::bind(&client_connection::loginPassPrompt, shared_from_this(), boost::asio::placeholders::error ));
    }
    else
    {
        disconnect();
    }
    
}



void client_connection::loginPassPrompt(const boost::system::error_code& error)
{
    if(!error)
    {
        boost::asio::async_write(socket_, boost::asio::buffer(string("Password: \r\n\r\n")), boost::bind(&client_connection::loginGetPass, shared_from_this(), boost::asio::placeholders::error ));
    }
    else
    {
        disconnect();
    }
    
    
    
}




void client_connection::loginGetPass(const boost::system::error_code& error)
{
    if(!error)
    {
        boost::asio::async_read_until(socket_, *pass_feed_, "\r\n", boost::bind(&client_connection::login, shared_from_this(), boost::asio::placeholders::error ));
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
        std::string garbage;
        std::istream userStream(username_feed_);
        std::istream passStream(pass_feed_);
        //is >> user >> pass >> garbage;
        
        userStream >> user;
        passStream >> pass;
        
        delete username_feed_;
        delete pass_feed_;
        
        username_feed_ = new boost::asio::streambuf;
        pass_feed_ = new boost::asio::streambuf;
        
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
                boost::asio::async_write(socket_, boost::asio::buffer(string("Invalid Username or Password - Syntax(username password) \r\n\r\n")), boost::bind(&client_connection::startSession, shared_from_this(), boost::asio::placeholders::error ));
            }
            else
            {
                sessionToken = dbEngine->GenerateToken(user, pass);
                boost::regex e("[\\']");
                std::string cleanUser = boost::regex_replace(user, e, "");
                
                std::ifstream ifs("data/ents/" + dbEngine->getDatFilename(user, sessionToken));
                boost::archive::binary_iarchive ia(ifs);
                
                ia >> tmpEntity;
                
                player = &tmpEntity;

                
                extern WorldMap *worldMap;
                               
                
                
                player->setSymbol((wchar_t *)player->wSymbol.c_str());
                
                worldMap->addEntToCenter(player);
                parser = new InputParser(player);
                
                //updatePlayerMap();
                
                std::string message("  " + user + " - " + "Has logged in.\r\n");
                client_pool_.deliver(message);
                
                boost::asio::async_write(socket_, boost::asio::buffer(string("\nGreetings, " + user + "\nWelcome To The ASCII Project!\r\n\r\n")), boost::bind(&client_connection::receive_command, shared_from_this(), boost::asio::placeholders::error ));
            }
        }
        
    }
    else
    {
        disconnect();
    }
    
}






void client_connection::newAccountGetUser(const boost::system::error_code& error)
{
    if(!error)
    {
        boost::asio::async_read_until(socket_, *username_feed_, "\r\n", boost::bind(&client_connection::newAccountGetPassPrompt, shared_from_this(), boost::asio::placeholders::error ));
    }
    else
    {
        disconnect();
    }
    
}



void client_connection::newAccountGetPassPrompt(const boost::system::error_code& error)
{
    if(!error)
    {
        boost::asio::async_write(socket_, boost::asio::buffer(string("Password: \r\n\r\n")), boost::bind(&client_connection::newAccountGetPass, shared_from_this(), boost::asio::placeholders::error ));
    }
    else
    {
        disconnect();
    }
    
    
    
}




void client_connection::newAccountGetPass(const boost::system::error_code& error)
{
    if(!error)
    {
        boost::asio::async_read_until(socket_, *pass_feed_, "\r\n", boost::bind(&client_connection::createAccount, shared_from_this(), boost::asio::placeholders::error ));
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
        std::string garbage;
        std::istream userStream(username_feed_);
        std::istream passStream(pass_feed_);
        //is >> user >> pass >> garbage;
        
        userStream >> user;
        passStream >> pass;
        
        delete username_feed_;
        delete pass_feed_;
        
        username_feed_ = new boost::asio::streambuf;
        pass_feed_ = new boost::asio::streambuf;
        
        delete line_command_;
        line_command_ = new boost::asio::streambuf;
        
        
        if( user.compare("") == 0 || pass.compare("") == 0)
        {
            boost::asio::async_write(socket_, boost::asio::buffer(string("New Account Syntax(username password) \r\n\r\n")), boost::bind(&client_connection::startSession, shared_from_this(), boost::asio::placeholders::error ));
        }
        else
        {
            extern DBConnector *dbEngine;
            if(dbEngine->AddAccount(user, pass))
            {
                cout << dbEngine->getDatFilename(user, dbEngine->GenerateToken(user, pass)) << endl;
                
                boost::asio::async_write(socket_, boost::asio::buffer(string("Account Created, you may now login \r\n\r\n")), boost::bind(&client_connection::startSession, shared_from_this(), boost::asio::placeholders::error ));
            }
            else
            {
                boost::asio::async_write(socket_, boost::asio::buffer(string("Username Already Exists \r\n\r\n")), boost::bind(&client_connection::startSession, shared_from_this(), boost::asio::placeholders::error ));
            }
            
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
        
        
              
        
        if( command == "" )
        {
            boost::asio::async_write(socket_, boost::asio::buffer(string("\r\n\r\n")), boost::bind(&client_connection::receive_command, shared_from_this(), boost::asio::placeholders::error ));
        }
        else if(command == "mapReset")
        {
            //  if(dbEngine->isValidToken( user, token))
            {
                forceReset = true;
                boost::asio::async_write(socket_, boost::asio::buffer(string("\r\n\r\n")), boost::bind(&client_connection::receive_command, shared_from_this(), boost::asio::placeholders::error ));
            }
            //  else
            //  {
            //     disconnect();
            // }
        }
        else if( command == "getToken")
        {
            sessionToken = dbEngine->GenerateToken(user, pass);
            boost::asio::async_write(socket_, boost::asio::buffer(string(sessionToken + "\r\n\r\n")), boost::bind(&client_connection::receive_command, shared_from_this(), boost::asio::placeholders::error ));
        }
        else if( command == "startMapStream")
        {
           // if(dbEngine->isValidToken( user, token))
            {
                
                updatePlayerMap();
                free(mapSize);
                mapSize = new char[16];
                
                memset(mapSize, '\0', 16);
                
                sprintf(mapSize, "%d\r\n\r\n", (int)len);
                
                // int x = atoi(mapSize);
                //  printf("map is %d\n", x);
                std::string mSize(mapSize);
                boost::asio::async_write(socket_, boost::asio::buffer(mSize), boost::bind(&client_connection::clientAcceptMapSize, shared_from_this(), boost::asio::placeholders::error));
            }
          //  else
          //  {
         //       disconnect();
         //   }
            
            
        }
        else if(command == "chat" || command == "Chat")
        {
            //boost::asio::async_read_until(socket_, *chat_message_, "\r\n", boost::bind(&client_connection::handleChatInput, shared_from_this(), boost::asio::placeholders::error ));
            
            std::string outboundMessage(chatStream);
            chatStream.clear();
            chatStream.append("\r\n");
            
            
            boost::asio::async_write(socket_, boost::asio::buffer(string(outboundMessage + "\r\n")), boost::bind(&client_connection::handleChatInput, shared_from_this(), boost::asio::placeholders::error ));
        }
        
        else if( command == "quit")
        {
            
            disconnect();
            
        }
        else if(isInteger(command))
        {
            //  if(dbEngine->isValidToken( user, token))
            {
                parser->handleAPI(atoi(command.c_str()));
                boost::asio::async_write(socket_, boost::asio::buffer(string("\r\n\r\n")), boost::bind(&client_connection::receive_command, shared_from_this(), boost::asio::placeholders::error ));
            }
            //  else
            //  {
            //     disconnect();
            // }
        }
        else
        {
            std::string parsedOutput;
            parsedOutput = parser->parse(command);
            
            boost::asio::async_write(socket_, boost::asio::buffer(string(parsedOutput + "\r\n\r\n")), boost::bind(&client_connection::receive_command, shared_from_this(), boost::asio::placeholders::error ));
            
        }
        
    }
    
    else
    {
        disconnect();
    }
}



void client_connection::handleChatInput(const boost::system::error_code &error)
{
    if (!error)
    {
            
        boost::asio::async_read_until(socket_, *chat_message_, "\r\n", boost::bind(&client_connection::handleChatOutput, shared_from_this(), boost::asio::placeholders::error )); 
    }
    else
    {
        disconnect();
    }
    
}










void client_connection::sizeChatOutput(const boost::system::error_code &error)
{
    if (!error)
    {
        
        // boost::asio::async_write(socket_, boost::asio::buffer(std::string(user + ": " + message)), boost::bind(&client_connection::receive_command, shared_from_this(), boost::asio::placeholders::error));
    }
    else
    {
        disconnect();
    }
    
}





void client_connection::handleChatOutput(const boost::system::error_code &error)
{
    if (!error)
    {
        
        
        std::string message, poolMessage;
        
        std::istream is(chat_message_);
        
        getline(is, message, '\0');
        
        if(message != "\r\n")
        {
            
            poolMessage.append(user + ": " + message);
            
            client_pool_.deliver(poolMessage);
        }
        
        delete chat_message_;
        chat_message_ = new boost::asio::streambuf;

        
        boost::asio::async_write(socket_, boost::asio::buffer(std::string("\r\n\r\n")), boost::bind(&client_connection::receive_command, shared_from_this(), boost::asio::placeholders::error));
        
        
        //boost::asio::async_write(socket_, boost::asio::buffer(std::string(user + ": " + message + "\r\n\r\n")), boost::bind(&client_connection::receive_command, shared_from_this(), boost::asio::placeholders::error));
        
        
        //boost::asio::async_read_until(socket_, *chat_message_, "\r\n", boost::bind(&client_connection::handleChatOutput, shared_from_this(), boost::asio::placeholders::error ));
        
       // boost::asio::async_write(socket_, boost::asio::buffer(std::string(user + ": " + message)), boost::bind(&client_connection::receive_command, shared_from_this(), boost::asio::placeholders::error));
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
    
    mapBuf->clear();
    
    
    player->clientFovSync(forceReset);
    //player->refreshFov();
    forceReset = false;
    
    renderForPlayer(player, mapBuf, savedMap);
    
    
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
        
    // We start off by mapping our numpad keys
    // To movement directions
    extern WorldMap *worldMap;
    
    if ( api == 0)
    {
        worldMap->moveEnt(player, 0, 0);
    }
    else if ( api == 1)
    {
        //player->move(-1, 1);
        worldMap->moveEnt(player, -1, 1);
    }
    else if ( api == 11)
    {
        player->removeWall(-1, 1);
    }
    else if ( api == 21)
    {
        player->placeWall(-1, 1);
    }
    else if ( api == 31)
    {
        player->placeFloor(-1, 1);
    }
    else if ( api == 41)
    {
        player->digHole(-1, 1);
    }
    
    
    else if ( api == 2)
    {
        //player->move(0, 1);
        worldMap->moveEnt(player, 0, 1);
    }
    else if ( api == 12)
    {
        player->removeWall(0, 1);
    }
    else if ( api == 22)
    {
        player->placeWall(0, 1);
    }
    else if ( api == 32)
    {
        player->placeFloor(0, 1);
    }
    else if ( api == 42)
    {
        player->digHole(0, 1);
    }
    
    
    
    else if ( api == 3)
    {
        //player->move(1, 1);
        worldMap->moveEnt(player, 1, 1);
    }
    else if ( api == 13)
    {
        player->removeWall(1, 1);
    }
    else if ( api == 23)
    {
        player->placeWall(1, 1);
    }
    else if ( api == 33)
    {
        player->placeFloor(1, 1);
    }
    else if ( api == 43)
    {
        player->digHole(1, 1);
    }
    
    
    
    else if (api == 4)
    {
        //player->move(-1, 0);
        worldMap->moveEnt(player, -1, 0);
    }
    else if ( api == 14)
    {
        player->removeWall(-1, 0);
    }
    else if ( api == 24)
    {
        player->placeWall(-1, 0);
    }
    else if ( api == 34)
    {
        player->placeFloor(-1, 0);
    }
    else if ( api == 44)
    {
        player->digHole(-1, 0);
    }
    
    
    
    else if (api == 5)
    {
        worldMap->changEntZ(player, 1);
    }
    
    
    else if ( api == 15)
    {
        worldMap->changEntZ(player, -1);
    }

    else if ( api == 25)
    {
        player->digUp();
    }
    
    else if ( api == 35)
    {
        player->digDown();
    }
    
    
    else if (api == 6)
    {
        //player->move(1, 0);
        worldMap->moveEnt(player, 1, 0);
    }
    else if ( api == 16)
    {
        player->removeWall(1, 0);
    }
    else if ( api == 26)
    {
        player->placeWall(1, 0);
    }
    else if ( api == 36)
    {
        player->placeFloor(1, 0);
    }
    else if ( api == 46)
    {
        player->digHole(1, 0);
    }
    
    
    
    else if (api == 7)
    {
        //player->move(-1, -1);
        worldMap->moveEnt(player, -1, -1);
    }
    else if ( api == 17)
    {
        player->removeWall(-1, -1);
    }
    else if ( api == 27)
    {
        player->placeWall(-1, -1);
    }
    else if ( api == 37)
    {
        player->placeFloor(-1, -1);
    }
    else if ( api == 47)
    {
        player->digHole(-1, -1);
    }
    
    
    
    else if (api == 8)
    {
        //player->move(0, -1);
        worldMap->moveEnt(player, 0, -1);
    }
    else if ( api == 18)
    {
        player->removeWall(0, -1);
    }
    else if ( api == 28)
    {
        player->placeWall(0, -1);
    }
    else if ( api == 38)
    {
        player->placeFloor(0, -1);
    }
    else if ( api == 48)
    {
        player->digHole(0, -1);
    }
    
    
    
    else if (api == 9)
    {
        //player->move(1, -1);
        worldMap->moveEnt(player, 1, -1);
    }
    else if ( api == 19)
    {
        player->removeWall(1, -1);
    }
    else if ( api == 29)
    {
        player->placeWall(1, -1);
    }
    else if ( api == 39)
    {
        player->placeFloor(1, -1);
    }
    else if ( api == 49)
    {
        player->digHole(1, -1);
    }
    
}




void client_connection::disconnect()
{
    
    
    free(stream);
    free(mapSize);
    
    delete mapBuf;
    delete savedMap;
    
    if(player != nullptr)
    {
        //extern EntityMap *entMap;
        //entMap->removeFromEntMap(player);
        //delete player;
        extern WorldMap *worldMap;
        worldMap->removeEnt(player);
        //delete player;
        
    }
        
    std::string message(user + " - " + "Has Disconnected.\r\n");
    client_pool_.deliver(message);
    
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
































