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
    
    kickStart();
}






void client_connection::kickStart()
{
    
    setlocale(LC_ALL, "");
        
    const char CHAR_MODE[] = "\377\375\x22\n";
    const char CLEAR_CON[] = "\x1b[2J";
    const char MOVE_CURS[] = "\x1b[H";
    
    std::cout << CHAR_MODE << "testing" << std::endl;
    std::cout << "\u2603";
    
    std::string topbar, bottombar, borders;
    
    topbar = "\u250F";
    bottombar = "\u2517";
    for(int x=0; x < 78; x++)
    {
        topbar.append("\u2501");
        bottombar.append("\u2501");
    }
    topbar.append("\u2513");
    bottombar.append("\u251B");

    for(int x=3; x < 24; x++)
    {
        
        std::string count;
        std::stringstream out;
        out << x;
        count = out.str();
        std::string line("\x1b[1H");
        line.replace(2, 1, count);

        line.append("\u2503");
        
        borders.append(line);
        
        cout << line << endl;
        
    }
    
    boost::asio::async_write(socket_, boost::asio::buffer(display->returnDisplay()), boost::bind(&client_connection::startSession, shared_from_this(), boost::asio::placeholders::error ));
    
    
/*
    borders.append("\x1b[3H\u2503\x1b[3;80H\u2503");
    borders.append("\x1b[4H\u2503\x1b[4;80H\u2503");
    borders.append("\x1b[5H\u2503\x1b[5;80H\u2503");
    borders.append("\x1b[6H\u2503\x1b[6;80H\u2503");
    borders.append("\x1b[7H\u2503\x1b[7;80H\u2503");
    borders.append("\x1b[8H\u2503\x1b[8;80H\u2503");
    borders.append("\x1b[9H\u2503\x1b[9;80H\u2503");
    borders.append("\x1b[10H\u2503\x1b[10;80H\u2503");
    borders.append("\x1b[11H\u2503\x1b[11;80H\u2503");
    borders.append("\x1b[12H\u2503\x1b[12;80H\u2503");
    borders.append("\x1b[13H\u2503\x1b[13;80H\u2503");
    borders.append("\x1b[14H\u2503\x1b[14;80H\u2503");
    borders.append("\x1b[15H\u2503\x1b[15;80H\u2503");
    borders.append("\x1b[16H\u2503\x1b[16;80H\u2503");
    borders.append("\x1b[17H\u2503\x1b[17;80H\u2503");
    borders.append("\x1b[18H\u2503\x1b[18;80H\u2503");
    borders.append("\x1b[19H\u2503\x1b[19;80H\u2503");
    borders.append("\x1b[20H\u2503\x1b[20;80H\u2503");
    borders.append("\x1b[21H\u2503\x1b[21;80H\u2503");
    borders.append(topbar + "\x1b[22H\u2523\x1b[22;80H\u252B");
    borders.append("\x1b[23H\u2503\x1b[23;80H\u2503"); */

    
    
    /*boost::asio::async_write(socket_, boost::asio::buffer(string(CHAR_MODE) + string(CLEAR_CON) + string(MOVE_CURS) + string("\x1b[100\n  Welcome to The ASCII Project \x1b[5m\u263A\x1b[25m \n") + topbar + string(
                                                                 "\x1b[18H\x1b[34m  Commands Available: \n"
                                                                 "  -------------------\n"
                                                                 "\x1b[31m  login\n"
                                                                 "  newaccount\n"
                                                                 "  quit \x1b[32m \n"
                                                                 //"\u2588\u2588\u2588\u2588"
                                                                 "\x1b[24H\r\n")
                                                          + bottombar + borders + string("\x1b[K\x1b[23H\u2503 $> ")), boost::bind(&client_connection::startSession, shared_from_this(), boost::asio::placeholders::error )); */
    
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
        std::cout << command;

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
        
        delete line_command_;
        line_command_ = new boost::asio::streambuf;
        
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
            
            boost::asio::async_write(socket_, boost::asio::buffer(string("\x1b[3H\u2503\x1b[5m " + time + "\x1b[25m\x1b[23H\x1b[K\u2503 $> \x1b[23;80H\u2503\x1b[23;5H")), boost::bind(&client_connection::receive_command, shared_from_this(), boost::asio::placeholders::error ));
        }
        else if( command == "" )
        {
            boost::asio::async_write(socket_, boost::asio::buffer(string("\x1b[23H\x1b[K\u2503 $> \x1b[23;80H\u2503\x1b[23;5H")), boost::bind(&client_connection::receive_command, shared_from_this(), boost::asio::placeholders::error ));
        }
        else
        {
            boost::asio::async_write(socket_, boost::asio::buffer(string("\x1b[23H\x1b[K\u2503 $> \x1b[23;80H\u2503\x1b[23;5H")), boost::bind(&client_connection::receive_command, shared_from_this(), boost::asio::placeholders::error ));
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































