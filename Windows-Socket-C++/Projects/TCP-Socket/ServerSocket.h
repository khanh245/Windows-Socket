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
#include <future>

namespace Kronos
{
	/// <summary>
	/// Represents the server socket.
	/// </summary>
	class ServerSocket : public Socket
	{
	public:
		/// <summary>
		/// Intializes a new instance of the Server socket class.
		/// </summary>
		ServerSocket();

		/// <summary>
		/// Listens to incoming connection.
		/// </summary>
		void Listen();

		/// <summary>
		/// Binds to a port.
		/// </summary>
		/// <param name="port">The speicifc port.</param>
		void Bind(const int& port);

		/// <summary>
		/// Starts hosting the socket on a specific port.
		/// </summary>
		/// <param name="port">The port to host.</param>
		void StartHosting(const int& port);

		/// <summary>
		/// Starts hosting the socket on a specific port asynchronously.
		/// </summary>
		/// <param name="port">The port to host.</param>
		/// <returns>The value in future.</returns>
		std::shared_future<void> StartHostingAsync(const int& port);

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

	private:
		/// <summary>
		/// The is stopped flag.
		/// </summary>
		std::atomic_bool isStopped;
	};
}

#endif