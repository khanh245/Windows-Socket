#ifndef _NETWORK_THREAD_
#define _NETWORK_THREAD_

#pragma comment(lib, "ws2_32.lib")
#pragma warning(disable: 4996)

#include <WinSock2.h>

class NetworkThread
{
public:
	NetworkThread(const int& id = 0, const SOCKET& sock = NULL);
	~NetworkThread();

	int getThreadID() { return m_ThreadID; }
	SOCKET getThreadSocket() { return m_ThreadSocket; }

private:
	int m_ThreadID;
	SOCKET m_ThreadSocket;
};

#endif