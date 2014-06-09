#ifndef _CLIENTSOCKET_H_
#define _CLIENTSOCKET_H_

#include "Socket.h"

class ClientSocket : public Socket
{
public:
	void ConnectToServer(const char *ipAddress, int port);

	char* getServerIP() const;
	int	getServerPort() const;
};

#endif