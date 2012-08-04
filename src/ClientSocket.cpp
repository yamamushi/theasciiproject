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



ClientSession::ClientSession(boost::asio::io_service& io_service, tcp::resolver::iterator endpoint_iterator, ClientMap *client, GraphicsTCOD *screen) : io_service_(io_service), socket_(io_service)
{
    clientMap = client;
    output = screen;
    
    packer = new ClientMapPacker();
    
    mapSize = new char[16];
    
    cmd = new char[8];
    sprintf(cmd, "\r\n");
    
    command = "startMapStream\r\n";
    direction = "\r\n";
    
    m_pause = false;
    sent = true;
    
    boost::asio::async_connect(socket_, endpoint_iterator, boost::bind(&ClientSession::Connect, this, boost::asio::placeholders::error));
}




void ClientSession::Connect(const boost::system::error_code& error)
{
    if(!error)
    {
        cout << "Connected\n" << endl;
        
        boost::asio::async_write(socket_, boost::asio::buffer(string("startMapStream\r\n")), boost::bind(&ClientSession::sizeMap, this, boost::asio::placeholders::error));
    }
    else
    {
        cout << "Failed To Connect\n";
    }
    
}




void ClientSession::ignorePrompt(const boost::system::error_code& error)
{
    if(!error)
    {
        async_read_until(socket_, line_command_, prompt, boost::bind(&ClientSession::callNewMap, this, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
    }
}





void ClientSession::sizeMap(const boost::system::error_code& error)
{
    if(!error)
    {
        
        //boost::asio::async_read_until(socket_, line_command_, "\n", boost::bind(&ClientSession::confirmSize, this, boost::asio::placeholders::error ));
        boost::asio::async_read(socket_, boost::asio::buffer(mapSize, 16), boost::bind(&ClientSession::confirmSize, this, boost::asio::placeholders::error));
        
    }
    else
    {
        printf("Closing: ERROR\n");
        close();
    }
    
}


void ClientSession::confirmSize(const boost::system::error_code& error)
{
    if(!error)
    {
        output->render();
        
        std::string tmpHolder;
        
        for(int i=0; i < 16; i++)
        {
            if (isdigit(mapSize[i]))
            {
                tmpHolder += mapSize[i];
            }
        }
        
        std::istringstream conv(tmpHolder);
        conv >> mapSize_;
        
        
        mapSize_ = mapSize_;
        
        boost::asio::async_write(socket_, boost::asio::buffer(string("00")), boost::bind(&ClientSession::read_map, this, boost::asio::placeholders::error));
    }
    else
    {
        printf("Closing: ERROR\n");
        close();
    }
    
    
}






void ClientSession::read_map(const boost::system::error_code& error)
{
    block_while_paused();
    
    if(!error)
    {
        
        buf = new char[mapSize_];
        
        
        boost::asio::async_read(socket_, boost::asio::buffer(buf, mapSize_), boost::bind(&ClientSession::callNewMap, this, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
        
        
    }
    else
    {
        printf("Closing: ERROR\n");
        close();
    }
}


void ClientSession::callNewMap(const boost::system::error_code& error, std::size_t bytes_transferred)
{
    block_while_paused();
    if(!error)
    {
        
        int offset = 0;
        
        for(int x=0; x < 128; x++)
        {
            if(strcmp(&buf[x], "t"))
            {
                offset = x;
                break;
            }
            
        }
        
        
        int count = 0;
        
        for(int x = 0; x < (bytes_transferred/TILE_PACKET_SIZE); x++)
        {
            char *unpack = new char[TILE_PACKET_SIZE];
            
            memset(unpack, '\0', TILE_PACKET_SIZE);
            memcpy(unpack, &buf[((x*TILE_PACKET_SIZE)+offset) - 1], TILE_PACKET_SIZE);
            
            
            packer->unpackFromNet(clientMap, (unsigned char*)unpack, output);
            
            free(unpack);
            count++;
        }
        
        output->render();
        
        
        sprintf(cmd, "\r\n");
        command = "startMapStream\r\n";
        // direction = "\r\n";
        block_while_paused();
        if(sent)
        {
            boost::asio::async_write(socket_, boost::asio::buffer(direction), boost::bind(&ClientSession::sendMapRequest, this, boost::asio::placeholders::error));
        }
        else
        {
            
            boost::asio::async_write(socket_, boost::asio::buffer(direction), boost::bind(&ClientSession::sendMapRequest, this, boost::asio::placeholders::error));
        }
    }
    else
    {
        printf("Closing: ERROR\n");
        close();
    }
    
}





void ClientSession::sendMapRequest(const boost::system::error_code& error)
{
    if(!error)
    {
        direction = "\r\n";
        
        block_while_paused();
        sleep(0.1);
        boost::asio::async_write(socket_, boost::asio::buffer(command), boost::bind(&ClientSession::sizeMap, this, boost::asio::placeholders::error));
        
    }
    
}





void ClientSession::sendAPICall(int api)
{
    std::ostringstream oss;
    oss << api;

        direction += oss.str();
        direction.append("\r\n");
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



















