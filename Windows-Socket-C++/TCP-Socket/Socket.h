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
	class Socket
	{
	protected:
		WSADATA wsaData;
		SOCKET mySocket;
		SOCKET myBackup;
		SOCKET acceptSocket;

		sockaddr_in myAddress;
		sockaddr_in otherAddress;

		int mPort;
		char* mIP;

	public:
		Socket();
		~Socket();

		int SendData(std::string&);
		int RecvData(std::string&);
		int RecvDelayed(std::string&, const int& _timeout = 3);
		bool isDataAvail();

		int CloseConnection();
		int Shutdown(const int& how);
		void GetAndSendMessage();

		int getPort() const { return mPort; }
		char* getIP() const { return mIP; }
	};
}

#endif