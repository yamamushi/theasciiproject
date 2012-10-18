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
#include <sstream>

#include "ServerSocket.h"
#include "Keyboard.h"


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
    //std::for_each(clients_.begin(), clients_.end(), boost::bind(&client_participant::addToChatStream, _1, message));
}









tcp::socket& client_connection::socket()
{
    return socket_;
}


void client_connection::start()
{
    
    line_command_ = new boost::asio::streambuf;
    
    client_pool_.join(shared_from_this());
    

    stream = new char[128];
    socket_.set_option(tcp::no_delay(true));
    
    display = new Display(80,24);
    keyboard = new Keyboard(display);
    
    kickStart();
}






void client_connection::kickStart()
{
    
    setlocale(LC_ALL, "");
        
 //   const char CHAR_MODE[] = "\377\375\x22\n";
 //   const char CLEAR_CON[] = "\x1b[2J";
 //   const char MOVE_CURS[] = "\x1b[H";
    
    boost::asio::async_write(socket_, boost::asio::buffer(display->returnDisplay()), boost::bind(&client_connection::receive_command, shared_from_this(), boost::asio::placeholders::error ));

    
}



void client_connection::startSession(const boost::system::error_code& error)
{
    if (!error)
    {
        
        delete line_command_;
        line_command_ = new boost::asio::streambuf;
        
        boost::asio::async_read_until(socket_, *line_command_, "*", boost::bind(&client_connection::receive_command, shared_from_this(), boost::asio::placeholders::error ));
        //boost::asio::async_read(socket_, boost::asio::buffer(stream, 1), boost::bind(&client_connection::receive_command, shared_from_this(), boost::asio::placeholders::error ));
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
        std::istream is(line_command_);
        std::string command;
        is >> command;
        //std::cout << command;

        
        boost::asio::async_read_until(socket_, *line_command_, "", boost::bind(&client_connection::handle_request_line, shared_from_this(), boost::asio::placeholders::error ));
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
        
        std::string command, token;
        
        std::istream is(line_command_);
        is >> command >> token ;
        cout << command << endl;
        
        std::vector<char> cmd(128);
        
        delete line_command_;
        line_command_ = new boost::asio::streambuf;
        
        keyboard->parseKey(command);
        
        if( command == "q")
        {
            
            disconnect();
            
        }
        else if(command == "w")
        {
            
            std::string flower("\x1b[2J\x1b[H\x1b[7h\x1b[0;1;40;37m\x1b[?33h\n"
                               "\x1b[18C\x1b[5m..\x1b[25m\x1b[10C\x1b[0m\x1b[7C\x1b[34m€€€€€€€€€€€\x1b[37m\x1b[19C\x1b[1m   \x1b[5m..\x1b[25m\n"
                               "\x1b[18C\x1b[5m..\x1b[25m\x1b[10C\x1b[0m    \x1b[34m€€€\x1b[37m \x1b[34m.,;;;;;,.\x1b[37m \x1b[34m€€€\n"
                               "\x1b[1;37m\x1b[30C\x1b[0m  \x1b[34m€€\x1b[37m \x1b[34m.,%!&&!%;%%%,.\x1b[37m  \x1b[34m€€\x1b[37m\x1b[14C\x1b[1m\x1b[6C.,,;%\n"
                               "\x1b[29C\x1b[0m \x1b[34m€€.,\x1b[32m%!&\x1b[34m###&!!&@@@&&!;.\x1b[37m \x1b[34m€€\x1b[37m\x1b[10C\x1b[1m...,,;!!%!&!%\n"
                               "\x1b[24C\x1b[0m\x1b[5C\x1b[34m€.\x1b[32m;&#@@@\x1b[34m@\x1b[32m@@@@@\x1b[34m@@@@@@@\x1b[32m@@&;\x1b[37m \x1b[34m€\x1b[37m   \x1b[1m.,,.,;%!!###@@!;%,\n"
                               "\x1b[25C\x1b[0m   \x1b[34m€\x1b[32m.;&@@@@@@@@@@@\x1b[34m@@@@@@\x1b[32m@@@@@\x1b[34m;.€\x1b[37m  \x1b[1m,%%;%!%%!#&%!&;\n"
                               "\x1b[7C\x1b[5m..\x1b[25m\x1b[16C\x1b[0m  \x1b[34m€\x1b[32m,!#@@@@@@@@@@@@\x1b[34m@@@@@@\x1b[32m@@@@\x1b[34m@#;\x1b[37m \x1b[34m€\x1b[37m \x1b[1m.;%;;%%%%%,  \x1b[5m..\x1b[25m\n"
                               "\x1b[7C\x1b[5m..\x1b[25m\x1b[16C\x1b[0m  \x1b[34m€\x1b[32m;#@@@@@@@@@@@@\x1b[34m@@@@@@@@@@@@@%\x1b[37m \x1b[34m€\x1b[37m \x1b[1m,;%%,,;%;;;.\n"
                               "\x1b[17C\x1b[5m..\x1b[25m\x1b[7C\x1b[0m \x1b[34m€\x1b[32m%@@#@\x1b[34m@\x1b[32m@@@@@\x1b[34m@@#@@@@@@@@@@@@#%\x1b[37m \x1b[34m€\x1b[37m \x1b[1m;;;%.    .,.\n"
                               "\x1b[17C\x1b[5m..\x1b[25m\x1b[7C\x1b[0m \x1b[34m€,\x1b[32m%#&&\x1b[34m@@@#######@@@@@\x1b[32m@@@\x1b[34m@@\x1b[32m@#%\x1b[37m \x1b[34m€\x1b[37m \x1b[1m....\n"
                               "\x1b[26C\x1b[0m \x1b[34m€.,%!!##@@@@@#@#@@\x1b[32m@@@@@@@@@#;\x1b[37m \x1b[34m€\n"
                               "\x1b[1;37m\x1b[24C.,,.\x1b[0;34m€\x1b[37m \x1b[34m.;%&&#&#&##@@\x1b[32m@@@@@@@@@@#%\x1b[34m.€\n"
                               "\x1b[1;37m\x1b[21C;!%%%&%\x1b[0m \x1b[34m€\x1b[37m \x1b[34m.,%&@@@###@@\x1b[32m@@@@@@\x1b[34m&\x1b[32m&!!;\x1b[34m.€\x1b[1;37m\x1b[10C\x1b[5m..\x1b[25m\n"
                               "   .;,\x1b[10C.. ,%&#!;,%%.\x1b[0m \x1b[34m€€\x1b[37m  \x1b[34m.,;%!@@@@@\x1b[32m@@\x1b[34m@##%%,.€€\x1b[37m \x1b[1m\x1b[10C\x1b[5m..\x1b[25m\n"
                               "   .;,\x1b[7C,;,%!%!&%,,,,,;%,..\x1b[0;34m€€.,;;;%!&&&&&#&!,.€€\n"
                               "\x1b[1;37m\x1b[6C;%,;%;;!!%%%!&!;,,,,,,;,..\x1b[0m  \x1b[34m€€€.,;;%%%;;;,.€€\n"
                               "\x1b[37m \x1b[1m\x1b[5C;%,;%;;;,,..,;;,,.\x1b[5C\x1b[0m\x1b[8C\x1b[34m€€€€€€€€€€€\n");
            
            boost::asio::async_write(socket_, boost::asio::buffer(flower), boost::bind(&client_connection::disconnect, shared_from_this()));
            
        }
        else if( command == "t")
        {
            time_t rawtime;
            
            struct tm * timeinfo;
            time( &rawtime );
            timeinfo = localtime(&rawtime);
            
            string time = asctime(timeinfo);
            
            boost::asio::async_write(socket_, boost::asio::buffer(string("\x1b[2H\u2503\x1b[5m " + time + "\x1b[25m\x1b[23H\x1b[K\u2503$> \x1b[23;80H\u2503\x1b[23;5H")), boost::bind(&client_connection::receive_command, shared_from_this(), boost::asio::placeholders::error ));
        }
        else
        {
         //   socket_.async_read_some(boost::asio::buffer(cmd, 1), boost::bind(&client_connection::receive_command, shared_from_this(), boost::asio::placeholders::error ));
            
            boost::asio::async_write(socket_, boost::asio::buffer(string("\x1b[23H\x1b[K\u2503$> \x1b[23;80H\u2503\x1b[23;5H")), boost::bind(&client_connection::receive_command, shared_from_this(), boost::asio::placeholders::error ));
        }
        
    }
    
    else
    {
        disconnect();
    }
}





void client_connection::disconnect()
{
    
    
    free(stream);
    
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































