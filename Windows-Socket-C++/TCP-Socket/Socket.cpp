
#include "Socket.h"

#include <sstream>
#include <Windows.h>
#include <vector>
#include <fstream>
#include <ctime>

Socket::Socket()
{
	memset(&myAddress, 0, sizeof(sockaddr_in));
	memset(&otherAddress, 0, sizeof(sockaddr_in));

	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != NO_ERROR)
	{
		std::cerr << "Socket: Error with WSAStartup\n";
		system("pause");
		WSACleanup();
		exit(10);
	}

	mySocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (mySocket == INVALID_SOCKET)
	{
		std::cerr << "Socket: Error creating socket" << std::endl;
		system("pause");
		WSACleanup();
		exit(11);
	}

	myBackup = mySocket;
}

Socket::~Socket()
{
	if (mIP) memset(mIP, 0, sizeof(mIP));

	Shutdown(0);
	CloseConnection();
	WSACleanup();
}

int Socket::SendData(std::string& buffer)
{
	int rc = send(mySocket, buffer.c_str(), buffer.length(), 0);
	if (rc < 0)
	{
		std::cerr << "Socket: Error sending data." << std::endl;
		return -1;
	}

	std::cerr << "Socket: Sent " << rc << " bytes." << std::endl;
	return rc;
}

bool Socket::isDataAvail()
{
	timeval timeout;
	memset(&timeout, 0, sizeof(timeval));
	fd_set ready;
	FD_ZERO(&ready);
	FD_SET(mySocket, &ready);

	int selectResult = select(mySocket, &ready, 0, 0, &timeout);

	if (selectResult < 0)
		std::cerr << "Socket: Error in select()." << std::endl;
	else if (selectResult >= 0)
	{
		if (FD_ISSET(mySocket, &ready))
			return true;
	}

	return false;
}

bool Socket::incomingConnection()
{
	fd_set set;
	struct timeval timeout;
	int rv;
	FD_ZERO(&set); 
	FD_SET(mySocket, &set); 

	timeout.tv_sec = 20;
	timeout.tv_usec = 0;

	rv = select(mySocket, &set, NULL, NULL, &timeout);
	if (rv == -1)
	{
		std::cerr << "ServerSocket: Select() error in listening" << std::endl;
		return false;
	}
	else if (rv == 0)
	{
		std::cerr << "ServerSocket: Timeout on incoming connection" << std::endl;
		return false;
	}
	
	return true;
}

int Socket::RecvDelayed(std::string& buff, const int& _to)
{
	int rc = 0;
	char buf[256] = "";

	timeval timeout;
	timeout.tv_sec = _to;

	fd_set readfds;
	FD_ZERO(&readfds);
	FD_SET(mySocket, &readfds);
	std::stringstream ss;

	int selectResult = select(mySocket, &readfds, 0, 0, &timeout);

	switch (selectResult)
	{
	case -1:
		std::cout << "Error occurred in select()." << std::endl;
		return -1;
	case 0:
		std::cerr << "Timeout." << std::endl;
		break;
	default:
		while (rc == 0) {
			if (FD_ISSET(mySocket, &readfds))
			{
				rc = RecvData(buff);
				if (rc < 0)
				{
					std::cerr << "Error trying to read from SOCKET." << std::endl;
					break;
				}
				/*
				rc = recv(mySocket, buf, 2, 0);
				if (rc < 0) cout << "Error reading from socket." << endl;
				else
				{
					int len = (int)buf[1];
					ss.clear();

					rc = recv(mySocket, buf, len, 0);
					for (int i = 0; i < len; i++)
						ss << buf[i];
					buff.clear();
					buff = ss.str();
				}*/
			}
		}

		break;
	}

	return rc;
}

int Socket::RecvData(std::string& buff)
{
	char buf[256];

	/// Reading the header length (2 bytes)
	int rc = recv(mySocket, buf, 2, 0);				
	if (rc < 0) return -1;

	int len = (int)buf[1];

	rc = recv(mySocket, buf, len, 0);
	if (rc < 0) return -1;

	std::stringstream ss1;
	for (int i = 0; i < rc; i++)
		ss1 << buf[i];
	buff.clear();
	buff = ss1.str();

	std::cerr << "Socket: Received " << rc << " bytes." << std::endl;
	return rc;
}

int Socket::CloseConnection()
{
	int rc = closesocket(mySocket);
	mySocket = myBackup;

	return rc;
}

int Socket::Shutdown(const int& how)
{
	int rc = shutdown(mySocket, how);
	mySocket = myBackup;

	return rc;
}

void Socket::GetAndSendMessage()
{
	std::string message;
	std::cout << "Send > ";
	std::getline(std::cin, message, '\n');
	SendData(message);

	///without this, it gets the return char from the last cin and ignores the following one!
	std::cin.ignore();	
}