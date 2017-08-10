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
	/// <summary>
	/// Represents a client socket.
	/// </summary>
	class ClientSocket : public Socket
	{
	public:
		/// <summary>
		/// Connects to a server.
		/// </summary>
		/// <param name="ipAddress">The server's IP address.</param>
		/// <param name="port">The server's port.</param>
		void ConnectToServer(const char *ipAddress, int port);

		/// <summary>
		/// Gets the server IP.
		/// </summary>
		/// <returns>The server's IP address.</returns>
		char* ServerIPAddress() const;
		
		/// <summary>
		/// Gets the server port.
		/// </summary>
		/// <returns>The server port.</returns>
		int	ServerPort() const;
	};
}

#endif