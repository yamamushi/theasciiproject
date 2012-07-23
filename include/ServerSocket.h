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




class ServerSocket : public SocketHandler {

private:

    bool m_quit;

public:
	ServerSocket(StdLog *p);
	~ServerSocket();

	void List(TcpSocket *p);
	void SetQuit();
	bool Quit();

};




class DisplaySocketMenu : public TcpSocket {

private:


public:

	DisplaySocketMenu(ISocketHandler& h);
	void OnAccept();
	void OnLine(const std::string& line);

};







class SendRawMap : public SocketHandler {

private:

    unsigned char *buf;
    bool m_quit;

public:

    SendRawMap(StdLog *p);
    ~SendRawMap();

    void init(unsigned char *buffer);
    void TransmitRaw(TcpSocket *out);

    void List(TcpSocket *p);

    void SetQuit() {
        m_quit = true;
    }

    bool Quit() {
        return m_quit;
    }

};