#ifndef _SERVERSOCKET_H_
#define _SERVERSOCKET_H_

#include "Socket.h"

class ServerSocket : public Socket
{
public:
	void Listen();
	void Bind(int port);
	void StartHosting(int port);

	char* getClientIP(const int& id = 0) const;
	int	getClientPort(const int& id = 0) const;
};

#endif