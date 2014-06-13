/*********************************************************************
	Date: 06/12/2014
	Author: Khanh Nguyen

	File: ServerSocket.h
	Name: Server Socket Class
	Purpose: Multithreaded Server Socket Object
**********************************************************************/

#ifndef _SERVERSOCKET_H_
#define _SERVERSOCKET_H_

#include <vector>

#include "Socket.h"
#include "NetworkThread.h"

class ServerSocket : public Socket
{
public:
	void Listen();
	void Bind(int port);
	void StartHosting(int port);

	char* getClientIP(const int& id = 0) const;
	int	getClientPort(const int& id = 0) const;

private:
	std::vector<NetworkThread> m_ThreadPools;
};

#endif