
#include "Socket.h"

#include <sstream>
#include <Windows.h>
#include <ctime>

/// <inheritdoc />
Kronos::Socket::Socket() 
	: acceptSocket(0), port(0), ip(nullptr)
{
	memset(&address, 0, sizeof(sockaddr_in));
	memset(&clientAddress, 0, sizeof(sockaddr_in));

	if (WSAStartup(MAKEWORD(2, 2), &wsaStructure) != NO_ERROR)
	{
		std::cerr << "Socket: Error with WSAStartup\n";
		WSACleanup();
	}

	this->socketInstance = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (this->socketInstance == INVALID_SOCKET)
	{
		std::cerr << "Socket: Error creating socket" << std::endl;
		WSACleanup();
	}

	this->backupSocket = this->socketInstance;
}

/// <inheritdoc />
Kronos::Socket::~Socket()
{
	if (ip)
	{
		memset(ip, 0, sizeof ip);
	}

	Shutdown(0);
	Close();
	WSACleanup();
}

/// <inheritdoc />
int Kronos::Socket::Send(std::string& buffer) const
{
	auto rc = send(this->socketInstance, buffer.c_str(), buffer.length(), 0);
	if (rc < 0)
	{
		std::cerr << "Socket: Error sending data." << std::endl;
		return -1;
	}

	std::cerr << "Socket: Sent " << rc << " bytes." << std::endl;
	return rc;
}

/// <inheritdoc />
bool Kronos::Socket::isDataAvailable() const
{
	timeval timeout;
	memset(&timeout, 0, sizeof(timeval));
	fd_set ready;
	FD_ZERO(&ready);
	FD_SET(this->socketInstance, &ready);

	auto selectResult = select(this->socketInstance, &ready, nullptr, nullptr, &timeout);
	if (selectResult < 0)
		std::cerr << "Socket: Error in select()." << std::endl;
	else if (selectResult >= 0)
	{
		if (FD_ISSET(this->socketInstance, &ready))
		{
			return true;
		}
	}

	return false;
}

/// <inheritdoc />
int Kronos::Socket::Receive(std::string& buff, const int& timeout) const
{
	auto rc = 0;
	//char buf[256] = "";

	timeval timeValue;
	timeValue.tv_sec = timeout;

	fd_set readfds;
	FD_ZERO(&readfds);
	FD_SET(this->socketInstance, &readfds);
	std::stringstream ss;

	auto selectResult = select(this->socketInstance, &readfds, nullptr, nullptr, &timeValue);

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
			if (FD_ISSET(this->socketInstance, &readfds))
			{
				rc = this->Receive(buff);
				if (rc < 0)
				{
					std::cerr << "Error trying to read from SOCKET." << std::endl;
					break;
				}
				/*
				rc = recv(this->socketInstance, buf, 2, 0);
				if (rc < 0) std::cout << "Error reading from socket." << std::endl;
				else
				{
					int len = (int)buf[1];
					ss.clear();

					rc = recv(this->socketInstance, buf, len, 0);
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

/// <inheritdoc />
int Kronos::Socket::Receive(std::string& buff) const
{
	char buf[256];

	/// Reading the header length (2 bytes)
	auto rc = recv(this->socketInstance, buf, 2, 0);				
	if (rc < 0)
	{
		return -1;
	}

	auto len = static_cast<int>(buf[1]);

	rc = recv(this->socketInstance, buf, len, 0);
	if (rc < 0)
	{
		return -1;
	}

	std::stringstream ss1;
	for (auto i = 0; i < rc; i++)
	{
		ss1 << buf[i];
	}

	buff.clear();
	buff = ss1.str();

	std::cerr << "Socket: Received " << rc << " bytes." << std::endl;
	return rc;
}

/// <inheritdoc />
int Kronos::Socket::Close()
{
	auto rc = closesocket(this->socketInstance);
	this->socketInstance = this->backupSocket;

	return rc;
}

/// <inheritdoc />
int Kronos::Socket::Shutdown(const int& how)
{
	auto rc = shutdown(this->socketInstance, how);
	this->socketInstance = this->backupSocket;

	return rc;
}

/// <inheritdoc />
int Kronos::Socket::Port() const
{
	return this->port;
}

/// <inheritdoc />
char* Kronos::Socket::IPAddress() const
{
	return this->ip;
}

//void Kronos::Socket::GetAndSendMessage() const
//{
//	std::string message;
//	std::cout << "Send > ";
//	getline(std::cin, message, '\n');
//	this->Send(message);
//
//	///without this, it gets the return char from the last std::cin and ignores the following one!
//	std::cin.ignore();	
//}