#ifndef _KRONOSPAYLOAD_H_
#define _KRONOSPAYLOAD_H_

#include <iostream>
#include <string>
using namespace std;

const char MESSAGE_SEPARATOR = '|';

class KronosPayload
{
public:
	KronosPayload();
	~KronosPayload();

	virtual operator const char* () = 0;

private:

};

class FindleyRequestMessage	:	public KronosPayload
{
public:
	char MessageLength[2];
	char MessageType[3];
	char Timestamp[10];
	char RequestID[15];
	char Name[10];
	char ID[7];
	char DelayedTime[4];

	char ClientIP[15];
	char ClientPort[4];
	char SocketNumber[1];

	char ServerIP[15];
	char ServerPort[4];

	char Message[20];
	char ScenarioID[1];

	FindleyRequestMessage()
	{
		strcpy_s(MessageType, 3, "REQ");
	}

	operator const char*();
};

struct FindleyResponseMessage
{

};

#endif