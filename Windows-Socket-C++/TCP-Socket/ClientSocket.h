/*********************************************************************
	Date: 06/13/2014
	Author: Khanh Nguyen

	File: ClientSocket.h
	Name: Client Socket Class
	Purpose: Client Socket with TCP protocol
**********************************************************************/

#ifndef _CLIENTSOCKET_H_
#define _CLIENTSOCKET_H_

#include "Socket.h"

namespace Kronos
{
	class ClientSocket : public Socket
	{
	public:
		void ConnectToServer(const char *ipAddress, int port);

		char* getServerIP() const;
		int	getServerPort() const;
	};
}

#endif