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

class ClientMapPacker;


class tcp_connection
: public boost::enable_shared_from_this<tcp_connection>
{
    
private:
    tcp_connection(boost::asio::io_service& io_service) : socket_(io_service) {};
    
    void handle_write(size_t bytes);
    
    tcp::socket socket_;
    std::string message_;
    std::vector<char *> mapBuf;
    
    
public:
    
    typedef boost::shared_ptr<tcp_connection> pointer;
    static pointer create(boost::asio::io_service& io_service);
    tcp::socket& socket();
    
    void start();
    
    
};




class tcp_server
{
    
private:
    void start_accept();
    
    void handle_accept(tcp_connection::pointer new_connection, const boost::system::error_code& error);
    
    tcp::acceptor acceptor_;
    
public:
    tcp_server(boost::asio::io_service& io_service);
    
    
};