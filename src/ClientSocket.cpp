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

#include <mutex>

#include "constants.h"

#include "ClientSocket.h"

#include "ClientWidgets.h"
#include "Serialization.h"
#include "Graphics.h"



ClientSession::ClientSession(boost::asio::io_service& io_service, tcp::resolver::iterator endpoint_iterator, ClientMap *client, GraphicsTCOD *screen) : io_service_(io_service), socket_(io_service)
{
    clientMap = client;
    output = screen;
    
    endpoint_iterator_ = endpoint_iterator;
    
    line_command_ = new boost::asio::streambuf;
    line_feed_ = new boost::asio::streambuf;
    map_size_ = new boost::asio::streambuf;
    
    packer = new ClientMapPacker();
    
    mapSize = new char[16];
    
    cmd = new char[8];
    sprintf(cmd, "\r\n");
    
    command = "startMapStream\r\n";
    direction = "\r\n";
    prompt = "ascii=> ";
    
    m_pause = false;
    sent = true;
    
    
    
    commander = screen->chatBox;
    chatBox = screen->serverBox;
    
}


bool ClientSession::Connect()
{
    boost::system::error_code ec;
    boost::asio::connect(socket_, endpoint_iterator_, ec);
    if(ec)
    {
        return false;
    }
    else
    {
        socket_.set_option(boost::asio::socket_base::reuse_address(true));
        socket_.set_option(boost::asio::socket_base::keep_alive(true));
        return true;
    }
    
}


void ClientSession::getLoginScreen()
{
    
    boost::asio::streambuf buffer;
    
    boost::system::error_code ec;
    read_until(socket_, buffer, "\r\n\r\n", ec);
    if(!ec)
    {

        std::string serverResponse;
        
        std::istream is(&buffer);
        
        getline(is, serverResponse, '\0');
        
        commander->insertText(serverResponse);
        
        
    }
    
    else
    {
        commander->insertText("Error - Connection Closed");
        output->connected = false;
        close();
    }
}


void ClientSession::sendCommand(std::string command)
{
    
    command.erase(0, 1);
    
    command.append("\r\n");

    
    boost::system::error_code sendError;
    boost::asio::write(socket_, boost::asio::buffer(string(command)), sendError);
    if(sendError)
    {
        commander->insertText("Sending Error");
        output->connected = false;
        close();
    }
    
    
}




void ClientSession::sendChatMessage(std::string message)
{
    
    //message.append(" \r\n");
    
    boost::system::error_code sendError;
    boost::asio::write(socket_, boost::asio::buffer(string(message + "\r\n")), sendError);
    if(sendError)
    {
        commander->insertText("Sending Error");
        output->connected = false;
        close();
    }
    
    
}



void ClientSession::getChatMessage()
{
    
    
    boost::asio::streambuf buffer;
    
    boost::system::error_code ec;
    
    read_until(socket_, buffer, "\r\n\r\n", ec);
    if(!ec)
    {
        
        std::string serverResponse;
        
        std::istream is(&buffer);
        
        getline(is, serverResponse, '\0');
        
        if(serverResponse != "\r\n\r\n");
            chatBox->insertText(serverResponse);

        
    }
    else
    {
        commander->insertText("Error - Connection Closed");
        output->connected = false;
        close();
    }
    
    
}




void ClientSession::getResponse()
{
    boost::asio::streambuf buffer;
    
    boost::system::error_code ec;
    
    read_until(socket_, buffer, "\r\n\r\n", ec);
    if(!ec)
    {

        std::string serverResponse;
        
        std::istream is(&buffer);
        
        getline(is, serverResponse, '\0');

        
        commander->insertText(serverResponse);
        
        if(serverResponse.find("Welcome") != std::string::npos)
        {
            output->loggedIn = true;
            
        }
    }
    else
    {
        commander->insertText("Error - Connection Closed");
        output->connected = false;
        close();
    }
    
}



void ClientSession::ignoreResponse()
{
    boost::asio::streambuf buffer;
    
    boost::system::error_code ec;
    
    read_until(socket_, buffer, "\r\n\r\n", ec);
    if(!ec)
    {
        
        ;
        
    }
    else
    {
        commander->insertText("Error - Connection Closed");
        output->connected = false;
        close();
    }
    
}




void ClientSession::sizeMap()
{
    
    boost::system::error_code sendError;
    boost::asio::write(socket_, boost::asio::buffer(string("startMapStream\r\n")), sendError);
    
    if(sendError)
    {
        commander->insertText("Sending Error");
        output->connected = false;
        close();
    }
    
}


int ClientSession::confirmSize()
{
    boost::asio::streambuf buffer;
    boost::system::error_code ec;
    
    boost::asio::read_until(socket_, buffer, "\r\n\r\n", ec);
    if(!ec)
    {
        
        //cout << "Data Read" << endl;
        std::string serverResponse;
        
        std::istream is(&buffer);
        
        getline(is, serverResponse, '\0');
        //cout << serverResponse << endl;
        
        int size = atoi(serverResponse.c_str());
        return size;
        
        
    }
    else
    {
        commander->insertText("Error - Connection Closed");
        output->connected = false;
        close();
        return 0;
    }
}






void ClientSession::read_map(int dataSize)
{
    
    
    buf = new char[dataSize];
    
    
    boost::asio::read(socket_, boost::asio::buffer(buf, dataSize));
    
    int count = 0;
    
    for(int x = 0; x < (dataSize)/(TILE_PACKET_SIZE); x++)
    {
        char *unpack = new char[TILE_PACKET_SIZE];
        
        memset(unpack, '.', TILE_PACKET_SIZE);
        memcpy(unpack, &buf[(x*TILE_PACKET_SIZE) - 1], TILE_PACKET_SIZE);
        
        packer->unpackFromNet(clientMap, (unsigned char*)unpack, output);
        
        free(unpack);
        count++;
    }
    
    
    free(buf);
    
    
    
}





void ClientSession::sendAPICall(int api)
{
    
    // block_while_paused();
    
    sprintf(cmd, "%d", api);
    
    
}


void ClientSession::close()
{
    io_service_.post(boost::bind(&ClientSession::do_close, this));
}

void ClientSession::do_close()
{
    socket_.close();
}


void ClientSession::block_while_paused()
{
    boost::unique_lock<boost::mutex> lock(m_pause_mutex);
    while(m_pause)
    {
        m_pause_changed.wait(lock);
    }
}


void ClientSession::set_paused(bool new_value)
{
    {
        boost::unique_lock<boost::mutex> lock(m_pause_mutex);
        m_pause = new_value;
    }
    
    m_pause_changed.notify_all();
    
}



















