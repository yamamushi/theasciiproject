/*
 * =====================================================================================
 *
 *       Filename:  ClientSocket.h
 *
 *    Description:  Experimental Sockets Implementation
 *
 *        Version:  1.0
 *        Created:  07/20/2012 10:28 PM
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

class GraphicsTCOD;
class ClientMapPacker;

//typedef std::deque<chat_message> chat_message_queue;

class ClientSession
{
private:
    
    tcp::socket socket_;
    
    std::mutex commandMutex;
    
    std::ostringstream oss;
    
    int mapSize_;
    
    char *mapSize;
    char *cmd;
    bool sent;
    
    ClientMap *clientMap;
    ClientMapPacker *packer;
    GraphicsTCOD *output;
    
    
    char *buf;
    
    string prompt;
    string command;
    string direction;
    
    string sessionToken;
    
    bool m_pause;
    bool m2_pause;
    bool rendering;
    
    tcp::resolver::iterator endpoint_iterator_;
    
    boost::asio::io_service& io_service_;
    boost::asio::streambuf *line_command_;
    boost::mutex m_pause_mutex;
    boost::condition_variable m_pause_changed;
    
    
    boost::mutex m2_pause_mutex;
    boost::condition_variable m2_pause_changed;
    
    
    boost::asio::streambuf *line_feed_;
   
    

    
    
    void do_close();
    
    
public:
       
    
    bool writing;
    
    ClientSession(boost::asio::io_service& io_service, tcp::resolver::iterator endpoint_iterator, ClientMap *client, GraphicsTCOD *screen);
    void Connect();
    
    void ignorePrompt(const boost::system::error_code& error);
    
    
    void requestLogin(const boost::system::error_code& error);
    void sendCredentials(const boost::system::error_code& error);
    void receiveCredResponse(const boost::system::error_code& error);
    void handleCredResponse(const boost::system::error_code& error);
    
    
    
    void requestNewAccount(const boost::system::error_code& error);
    
    
    
    void sizeMap(const boost::system::error_code& error);
    void confirmSize(const boost::system::error_code& error);
    void read_map(const boost::system::error_code& error);
    void callNewMap(const boost::system::error_code& error, std::size_t bytes_transferred);
    
    void ignoreMap(const boost::system::error_code& error, std::size_t bytes_transferred);
    
    
    void sendMapRequest(const boost::system::error_code& error);
    
    void sendAPICall(int api);
    
    void write();
    void close();
    
    void kick(int x = 0);

    
    void block_while_paused();
    void set_paused(bool new_value);
    
    void block2_while_paused();
    void set2_paused(bool new_value);


};





















