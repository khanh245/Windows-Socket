#include "ClientSocket.h"

/// <inheritdoc />
void Kronos::ClientSocket::ConnectToServer(const char *ipAddress, int port)
{
	this->address.sin_family = AF_INET;
	this->address.sin_addr.s_addr = inet_addr(ipAddress);
	this->address.sin_port = htons(port);

	std::cout << "ClientSocket: Connecting to " << ipAddress << ":" << port << std::endl;

	if (connect(this->socketInstance, reinterpret_cast<sockaddr*>(&this->address), sizeof this->address) == SOCKET_ERROR)
	{
		std::cerr << "ClientSocket: Failed to connect\n";
		WSACleanup();
	}

	int len = sizeof this->address;
	memset(&this->address, 0, sizeof(sockaddr_in));
	getsockname(this->socketInstance, reinterpret_cast<sockaddr*>(&this->address), &len);

	auto temp = inet_ntoa(this->address.sin_addr);

	this->ip = new char[strlen(temp) + 1];
	memset(this->ip, 0, strlen(this->ip));
	memcpy(this->ip, temp, strlen(temp));
	
	this->port = htons(this->address.sin_port);

	len = sizeof this->clientAddress;
	getpeername(this->socketInstance, reinterpret_cast<sockaddr*>(&this->clientAddress), &len);

	std::cout << "Connected..." << std::endl;
}

/// <inheritdoc />
char* Kronos::ClientSocket::ServerIPAddress() const
{
	return inet_ntoa(this->clientAddress.sin_addr);
}

/// <inheritdoc />
int Kronos::ClientSocket::ServerPort() const
{
	return htons(this->clientAddress.sin_port);
}