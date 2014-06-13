/*********************************************************************
	Date: 06/13/2014
	Author: Khanh Nguyen

	File: ServerSocket.h
	Name: Server Socket Class
	Purpose: Server Socket with TCP protocol
**********************************************************************/

#ifndef _SERVERSOCKET_H_
#define _SERVERSOCKET_H_

#include "Socket.h"

namespace Kronos
{
	class ServerSocket : public Socket
	{
	public:
		void Listen();
		void Bind(int port);
		void StartHosting(int port);

		char* getClientIP(const int& id = 0) const;
		int	getClientPort(const int& id = 0) const;
	};
}

#endif