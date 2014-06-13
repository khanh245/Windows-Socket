#include "ServerSocket.h"

void ServerSocket::StartHosting(int port)
{
	Bind(port);
	Listen();
}

void ServerSocket::Listen()
{
	std::cout << std::endl << "ServerSocket: Listening for client..." << std::endl;

	if (listen(mySocket, 5) == SOCKET_ERROR)
	{
		std::cerr << "ServerSocket: Error listening on socket\n";
		WSACleanup();
	}

	std::cout << std::endl << "ServerSocket: Accepting connection..." << std::endl;

	acceptSocket = accept(mySocket, (sockaddr*)&otherAddress, (int*)sizeof(otherAddress));
	std::cout << "ServerSocket: Client connected: " << getClientIP() << ":" << getClientPort() << std::endl;

	while (acceptSocket < 0)
	{
		acceptSocket = accept(myBackup, NULL, NULL);
		std::cout << "ServerSocket: Client connected" << getClientIP() << ":" << getClientPort() << std::endl;
	}

	getpeername(acceptSocket, (sockaddr*)&otherAddress, (int*)sizeof(otherAddress));
	mySocket = acceptSocket;
}

void ServerSocket::Bind(int port)
{
	myAddress.sin_family = AF_INET;
	myAddress.sin_addr.s_addr = inet_addr("0.0.0.0");
	myAddress.sin_port = htons(port);
	int len = sizeof(myAddress);

	if (bind(mySocket, (sockaddr*)&myAddress, len) == SOCKET_ERROR)
	{
		std::cerr << "ServerSocket: Failed to connect\n";
		WSACleanup();
	}

	char hn[80] = "";
	gethostname(hn, sizeof(hn));
	struct hostent* hosts;
	hosts = gethostbyname(hn);
	
	int i = 0;
	in_addr addr;
	while (hosts->h_addr_list[i] != 0) i++;

	addr.s_addr = *(u_long *)hosts->h_addr_list[i-1];
	mIP = inet_ntoa(addr);
	mPort = htons(myAddress.sin_port);
}

char* ServerSocket::getClientIP(const int& id) const
{
	return inet_ntoa(otherAddress.sin_addr);
}

int ServerSocket::getClientPort(const int& id) const
{
	return htons(otherAddress.sin_port);
}