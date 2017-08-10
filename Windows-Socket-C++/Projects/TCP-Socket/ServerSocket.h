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
	/// <summary>
	/// Represents the server socket.
	/// </summary>
	class ServerSocket : public Socket
	{
	public:
		/// <summary>
		/// Listens to incoming connection.
		/// </summary>
		void Listen();

		/// <summary>
		/// Binds to a port.
		/// </summary>
		/// <param name="port">The speicifc port.</param>
		void Bind(int port);

		/// <summary>
		/// Starts hosting/listening to connection.
		/// </summary>
		/// <param name="port">The specific port.</param>
		void StartHosting(int port);

		/// <summary>
		/// Gets the client IP address.
		/// </summary>
		/// <param name="id">The client ID.</param>
		/// <returns>The client IP address.</returns>
		char* ClientIPAddress(const int& id = 0) const;

		/// <summary>
		/// Gets the client port.
		/// </summary>
		/// <param name="id">The client ID.</param>
		/// <returns>The client port.</returns>
		int	ClientPort(const int& id = 0) const;
	};
}

#endif