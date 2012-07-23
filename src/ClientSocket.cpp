/*
 * =====================================================================================
 *
 *       Filename:  ClientSocket.cpp
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

#include "headers.h"


ClientSocket::ClientSocket(ISocketHandler& h) : TcpSocket(h)
{
}

void ClientSocket::OnRead()
{
	// OnRead of TcpSocket actually reads the data from the socket
	// and moves it to the input buffer (ibuf)
	TcpSocket::OnRead();
	// get number of bytes in input buffer
	size_t n = ibuf.GetLength();
	if (n > 0)
	{
		char tmp[RSIZE]; // <--- tmp's here
		ibuf.Read(tmp,n);
		printf("Read %d bytes:\n",n);
		for (size_t i = 0; i < n; i++)
		{
			printf("%c",isprint(tmp[i]) ? tmp[i] : '.');
		}
		printf("\n");
	}
}


MapSocket::MapSocket(ISocketHandler& h) : TcpSocket(h)
{

}

void MapSocket::OnRead()
{

    TcpSocket::OnRead();
    printf("Received Raw Data\n");
    printf("Size of Raw Data is %d\n", ibuf.GetLength());
    char *buf = new char[ibuf.GetLength()];
    ibuf.Read( buf, ibuf.GetLength());

    ClientMapPacker *packer = new ClientMapPacker();
    printf("Packer Initialized\n");
    packer->unpackFromNet(dest, (unsigned char*)buf);
    out->render();
    out->clearScreen();

}

void MapSocket::loadClientMap(ClientMap *client){

    dest = client;

}

void MapSocket::assignLocalOut(GraphicsTCOD* screen)
{

    out = screen;

}