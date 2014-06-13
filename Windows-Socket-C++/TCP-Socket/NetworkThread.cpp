#include "NetworkThread.h"

NetworkThread::NetworkThread(const int& id, const SOCKET& sock) :
m_ThreadID(id),
m_ThreadSocket(sock)
{ }

NetworkThread::~NetworkThread()
{ }