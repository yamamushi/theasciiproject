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

#include "headers.h"



ServerSocket::ServerSocket(StdLog *p) : SocketHandler(p),m_quit(false)
{

}

ServerSocket::~ServerSocket()
{

}

void ServerSocket::List(TcpSocket *p)
{
    for (socket_m::iterator it = m_sockets.begin(); it != m_sockets.end(); it++) {
        Socket *p0 = (*it).second;
        if (dynamic_cast<TcpSocket *> (p0)) {
            p->Send("TcpSocket\n");
        } else {
            p->Send("Some kind of Socket\n");
        }
    }
}

void ServerSocket::SetQuit()
{
    m_quit = true;
}

bool ServerSocket::Quit()
{
    return m_quit;
}






DisplaySocketMenu::DisplaySocketMenu(ISocketHandler& h) : TcpSocket(h)
{
    // SetLineProtocol();
}

void DisplaySocketMenu::OnAccept()
{
   // Send("Cmd (list, quit , dump, stop)>");
    static_cast<SendRawMap&> (Handler()).TransmitRaw(this);
}

void DisplaySocketMenu::OnLine(const std::string& line)
{
    Parse pa(line);
    std::string cmd = pa.getword();
    std::string arg = pa.getrest();
    if (cmd == "list") {
        static_cast<SendRawMap&> (Handler()).List(this);
    } else
        if (cmd == "quit") {
        Send("Goodbye!\n");
        SetCloseAndDelete();
    } else
        if (cmd == "stop") {
        static_cast<SendRawMap&> (Handler()).SetQuit();
    } else {
        Send("Huh?\n");
    }
    Send("Cmd>");
}






SendRawMap::SendRawMap(StdLog *p) : SocketHandler(p),m_quit(false)
{
}

SendRawMap::~SendRawMap()
{

}

/*void SendRawMap::init(unsigned char *buf)
{

    buffer = buf;

} */

void SendRawMap::init(Entity *target){

    src = target;

}

void SendRawMap::TransmitRaw(TcpSocket *out)
{
    int x, y;
    for (x = 0; x < MAP_WIDTH; x++) {
        for (y = 0; y < MAP_HEIGHT; y++) {
            if ((src->fov[x][y])) {

                 ClientMapPacker *packer = new ClientMapPacker();
                 unsigned char *buffer = new unsigned char[128];
                 render_t tmp = *src->returnCMap()->cMap[x][y];
                 //render_t tmp = src->returnCMap()->cMap[src->posX()][src->posY()];
                 packer->packToNet(tmp, buffer);
                 printf("Size of Buffer being Sent %d\n", (unsigned)sizeof(buffer));
                 out->SendBuf(reinterpret_cast<const char*>(buffer), 128);
                 //delete packer;
                 //free(buffer);
            }
        }
    }
}

void SendRawMap::List(TcpSocket *p)
{
    for (socket_m::iterator it = m_sockets.begin(); it != m_sockets.end(); it++) {
        Socket *p0 = (*it).second;
        if (dynamic_cast<TcpSocket *> (p0)) {
            p->Send("TcpSocket\n");
        } else {
            p->Send("Some kind of Socket\n");
        }
    }
}
