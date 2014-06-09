#include "ClientSocket.h"

void ClientSocket::ConnectToServer(const char *ipAddress, int port)
{
	myAddress.sin_family = AF_INET;
	myAddress.sin_addr.s_addr = inet_addr(ipAddress);
	myAddress.sin_port = htons(port);

	cout << "ClientSocket: Connecting to " << ipAddress << ":" << port << endl;

	if (connect(mySocket, (sockaddr*) &myAddress, sizeof(myAddress)) == SOCKET_ERROR)
	{
		cerr << "ClientSocket: Failed to connect\n";
		WSACleanup();
	}

	int len = sizeof(myAddress);
	memset(&myAddress, 0, sizeof(sockaddr_in));
	getsockname(mySocket, (sockaddr*)&myAddress, &len);

	char* temp = inet_ntoa(myAddress.sin_addr);
	mIP = new char[strlen(temp) + 1];
	memset(mIP, 0, strlen(mIP));
	memcpy(mIP, temp, strlen(temp));
	mPort = htons(myAddress.sin_port);

	len = sizeof(otherAddress);
	getpeername(mySocket, (sockaddr*)&otherAddress, &len);

	cout << "Connected..." << endl;
}

char* ClientSocket::getServerIP() const
{
	return inet_ntoa(otherAddress.sin_addr);
}

int ClientSocket::getServerPort() const
{
	return htons(otherAddress.sin_port);
}