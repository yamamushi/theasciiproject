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


class ServerSocket : public SocketHandler
{
public:
	ServerSocket(StdLog *p) : SocketHandler(p),m_quit(false) {}
	~ServerSocket() {}

	void List(TcpSocket *p) {
		for (socket_m::iterator it = m_sockets.begin(); it != m_sockets.end(); it++)
		{
			Socket *p0 = (*it).second;
			if (dynamic_cast<PoolSocket *>(p0))
			{
				p -> Send("PoolSocket\n");
                        }
			else
			if (dynamic_cast<TcpSocket *>(p0))
			{
				p -> Send("TcpSocket\n");
			}
			else
			{
				p -> Send("Some kind of Socket\n");
			}
		}
	}
	void SetQuit() { m_quit = true; }
	bool Quit() { return m_quit; }

private:
	bool m_quit;
};



class DisplaySocketMenu : public TcpSocket {


public:
	DisplaySocketMenu(ISocketHandler& h) : TcpSocket(h) {
		SetLineProtocol();
	}
	void OnAccept() {
		Send("Cmd (list, quit ,stop)>");
	}
	void OnLine(const std::string& line) {
		Parse pa(line);
		std::string cmd = pa.getword();
		std::string arg = pa.getrest();
                if (cmd == "list")
		{
			static_cast<ServerSocket&>(Handler()).List( this );
		}
		else
		if (cmd == "quit")
		{
			Send("Goodbye!\n");
			SetCloseAndDelete();
		}
		else
		if (cmd == "stop")
		{
			static_cast<ServerSocket&>(Handler()).SetQuit();
		}
		else
		{
			Send("Huh?\n");
		}
		Send("Cmd>");
	}

};