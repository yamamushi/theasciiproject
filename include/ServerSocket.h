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




class client_participant
{
public:
    virtual ~client_participant() {}
    virtual void sync() = 0;
    virtual void updatePlayerMap() = 0;
};

typedef boost::shared_ptr<client_participant> client_participant_ptr;




class client_pool
{
private:
    std::set<client_participant_ptr> clients_;
        
public:
    void join(client_participant_ptr client);
    void leave(client_participant_ptr client);
    void deliver();
    
    
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
    
    std::string prompt = "";
    std::string sessionToken;
    std::string user;
    std::string pass;
    
    bool moved;
    
    std::size_t len;
    
    std::vector<char *> *mapBuf;
    
    ClientMap *cMap;
    
    tcp::socket socket_;
    client_pool& client_pool_;
    
    boost::asio::streambuf *username_feed_;
    boost::asio::streambuf *pass_feed_;
    
    boost::asio::streambuf *line_command_;
    
  
    
public:
    
    client_connection(boost::asio::io_service& io_service, client_pool& pool) : socket_(io_service), client_pool_(pool) {};
    
    tcp::socket& socket();
    void start();
    
    void kickStart();
    
    void startSession(const boost::system::error_code& error);
    void sessionStartHandler(const boost::system::error_code& error);
    
    void catchUsername(const boost::system::error_code& error);
    
    void startLogin(const boost::system::error_code& error);
    void loginUser(const boost::system::error_code& error);
    
    void catchPassword(const boost::system::error_code& error);
    void startPass(const boost::system::error_code& error);
    void loginPass(const boost::system::error_code& error);
    
    void loginGetUser(const boost::system::error_code& error);
    void loginPassPrompt(const boost::system::error_code& error);
    void loginGetPass(const boost::system::error_code& error);
    void login(const boost::system::error_code& error);
    
    
    void newAccountGetUser(const boost::system::error_code& error);
    void newAccountGetPassPrompt(const boost::system::error_code& error);
    void newAccountGetPass(const boost::system::error_code& error);
    void createAccount(const boost::system::error_code& error);
    
    
    
    
    
    void receive_command(const boost::system::error_code& error);
    
    void handle_request_line(const boost::system::error_code& error);
    
    void sync();
    void handle_write(size_t bytes, const boost::system::error_code& error);
    
    void clientAcceptMapSize(const boost::system::error_code& error);
    void sendMap(const boost::system::error_code& error);
    
    void disconnect();
    
    void updatePlayerMap();
    void handleAPI(int api);
    
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




























