/*********************************************************************
	Date: 06/08/2014
	Author: Khanh Nguyen

	File: Socket.h
	Name: Socket Class
	Purpose: Provide preliminary support for SOCKET
	Wrap the SOCKET in Winsock2 to use for Server/Client
	int TCP/IP communication, possibly UDP and generic data
	communication in network
**********************************************************************/

#ifndef _SOCKET_H_
#define _SOCKET_H_

#pragma comment(lib, "ws2_32.lib")
#pragma warning(disable: 4996)

#include <iostream>
#include <WinSock2.h>

namespace Kronos
{
	/// <summary>
	/// Represents the socket class.
	/// </summary>
	class Socket
	{
	protected:
		/// <summary>
		/// Intializes a new instance of the Socket class.
		/// </summary>
		Socket();

		/// <summary>
		/// Finalizes the Socket instance.
		/// </summary>
		~Socket();

		/// <summary>
		/// The WSADATA structure.
		/// </summary>
		WSADATA wsaStructure;

		/// <summary>
		/// The internal socket instance.
		/// </summary>
		SOCKET socketInstance;

		/// <summary>
		/// The backup socket instance.
		/// </summary>
		SOCKET backupSocket;

		/// <summary>
		/// The accept socket instance.
		/// </summary>
		SOCKET acceptSocket;

		/// <summary>
		/// The socket's IP address.
		/// </summary>
		sockaddr_in address;

		/// <summary>
		/// The socket's client's IP address.
		/// </summary>
		sockaddr_in clientAddress;

		/// <summary>
		/// The socket's port.
		/// </summary>
		int port;

		/// <summary>
		/// The socket's IP address.
		/// </summary>
		char* ip;

	public:
		/// <summary>
		/// Sends the desired data through the socket.
		/// </summary>
		/// <param name="data">The data to be sent.</param>
		/// <returns>The number of sent bytes.</returns>
		int Send(std::string& data) const;

		/// <summary>
		/// Receives data through the socket.
		/// </summary>
		/// <param name="result">The received data.</param>
		/// <returns>The number of received bytes.</returns>
		int Receive(std::string& result) const;

		/// <summary>
		/// Receives data through the socket with timeout.
		/// </summary>
		/// <param name="result">The received data.</param>
		/// <param name="timeout">The timeout.</param>
		/// <returns>The number of received bytes.</returns>
		int Receive(std::string& result, const int& timeout) const;

		/// <summary>
		/// Checks to see if any data is available.
		/// </summary>
		/// <returns><c>true</c> if data is available. <c>false</c> otherwise.</returns>
		bool IsDataAvailable() const;

		/// <summary>
		/// Closes the socket.
		/// </summary>
		/// <returns>A value indicates success.</returns>
		int Close();
		
		/// <summary>
		/// Shutdowns the socket.
		/// </summary>
		/// <param name="how">How the shutdown should be carried out.</param>
		/// <returns>A value indicates success.</returns>
		int Shutdown(const int& how);

		/// <summary>
		/// Gets the socket port number.
		/// </summary>
		/// <returns>The socket port number.</returns>
		int Port() const;

		/// <summary>
		/// Gets the socket's IP address.
		/// </summary>
		/// <returns>The socket's IP address.</returns>
		char* IPAddress() const;
	};
}

#endif