#include "ServerSocket.h"

/// <inheritdoc />
Kronos::ServerSocket::ServerSocket() :
	isStopped(false)
{
}


/// <inheritdoc />
void Kronos::ServerSocket::StartHosting(const int& port)
{
	Bind(port);
	Listen();
}

/// <inheritdoc />
std::shared_future<void> Kronos::ServerSocket::StartHostingAsync(const int& port)
{
	return std::async(std::launch::async, &ServerSocket::StartHosting, this, port);
}

/// <inheritdoc />
void Kronos::ServerSocket::Listen()
{
	std::cout << std::endl << "ServerSocket: Listening for client..." << std::endl;

	if (listen(this->socketInstance, 5) == SOCKET_ERROR)
	{
		std::cerr << "ServerSocket: Error listening on socket\n";
		WSACleanup();
	}

	std::cout << std::endl << "ServerSocket: Accepting connection..." << std::endl;
	int len = sizeof this->clientAddress;

	this->acceptSocket = accept(this->socketInstance, reinterpret_cast<sockaddr*>(&this->clientAddress), &len);
	std::cout << "ServerSocket: Client connected: " << this->ClientIPAddress() << ":" << this->ClientPort() << std::endl;

	getpeername(this->acceptSocket, reinterpret_cast<sockaddr*>(&this->clientAddress), reinterpret_cast<int*>(sizeof this->clientAddress));
	this->socketInstance = this->acceptSocket;
}

/// <inheritdoc />
void Kronos::ServerSocket::Bind(const int& port)
{
	this->address.sin_family = AF_INET;
	this->address.sin_addr.s_addr = inet_addr("0.0.0.0");
	this->address.sin_port = htons(port);
	int len = sizeof this->address;

	if (bind(this->socketInstance, reinterpret_cast<sockaddr*>(&this->address), len) == SOCKET_ERROR)
	{
		std::cerr << "ServerSocket: Failed to connect\n";
		WSACleanup();
	}

	char hn[80] = "";
	gethostname(hn, sizeof hn);
	auto hosts = gethostbyname(hn);

	auto i = 0;
	in_addr addr;
	while (hosts->h_addr_list[i] != nullptr)
	{
		i++;
	}

	addr.s_addr = *reinterpret_cast<u_long *>(hosts->h_addr_list[i - 1]);
	this->ip = inet_ntoa(addr);
	this->port = htons(this->address.sin_port);
}

/// <inheritdoc />
char* Kronos::ServerSocket::ClientIPAddress(const int& id) const
{
	return inet_ntoa(this->clientAddress.sin_addr);
}

/// <inheritdoc />
int Kronos::ServerSocket::ClientPort(const int& id) const
{
	return htons(this->clientAddress.sin_port);
}
