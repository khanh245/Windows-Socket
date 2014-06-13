#include <WinSock2.h>
#include <time.h>
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>

#include "Socket.h"
#include "ServerSocket.h"
#include "ClientSocket.h"

void client()
{
	clock_t req = 0;
	clock_t res = 0;
	clock_t mReq = 0;
	clock_t mRes = 0;

	srand((unsigned int)time(NULL));

	bool ready = false;
	ClientSocket sockClient;
	SYSTEMTIME st;

	std::cout << "Attempting to connect..." << std::endl;
	sockClient.ConnectToServer("127.0.0.1", 2605);

	int i = 0;
	std::ofstream file("ThreadedTestClient.txt");

	while (sockClient.isDataAvail() || i < 10000)
	{
		//int time = rand() % 4 + 1;

		const char* rest = "|1|10.220.8.170|6500|C'est La Vie|3|";
		char* mess = "|NguyenK519|19-9519|";
		//char* mess = "|NguyenK|18-8317|";

		/*
		char* t = "";
		switch (time)
		{
		case 1:
		t = "1000";
		break;
		case 2:
		t = "2000";
		break;
		case 3:
		t = "3000";
		break;
		case 4:
		t = "4000";
		break;
		}*/

		int port = sockClient.getPort();
		std::stringstream ss, ss3;

		GetLocalTime(&st);
		char timestamp[16] = { 0 };
		sprintf_s(timestamp, "%02d%02d%02d%04d", st.wHour, st.wMinute, st.wSecond, st.wMilliseconds);
		ss << "REQ|" << timestamp << "|ReqID564530" << i << mess << 0 << "|" << sockClient.getIP() << "|" << port << rest;
		std::string temp = ss.str();
		const char* message = temp.c_str();

		int l = strlen(message);
		unsigned char b1, b2;

		b1 = l & 255;
		b2 = (l >> 8) & 255;
		ss3 << b2 << b1 << message;

		std::string realMsg = ss3.str();
		std::string recMessage = "";

		req = clock();
		sockClient.SendData(realMsg);
		req = clock() - req;
		mReq += req;

		res = clock();
		sockClient.RecvData(recMessage);
		res = clock() - res;
		mRes += res;

		++i;
		file << realMsg << std::endl;
		file << recMessage << std::endl << std::endl;
	}

	file << "Requests transmitted = 10000" << std::endl;
	file << "Responses received = 10000" << std::endl;
	file << "Req. run duration (ms) = " << mReq << std::endl;
	file << "Res. run duration (ms) = " << mRes << std::endl;
	file << "Trans. run duration (ms) = " << mRes - 0 << std::endl;
	file << "Actual req. pace = " << mReq / 10000 << std::endl;
	file << "Actual res. pace = " << mRes / 10000 << std::endl;
	file << "Config. pace = " << 3 << std::endl;
	file << "Transaction avg. = " << mRes / 10000 << std::endl;
	file << "Your name: " << std::endl;
	file << "Name of the other student = " << std::endl;

	int shut = sockClient.Shutdown(0);
	int close = sockClient.CloseConnection();

	file.close();
}

void server()
{
	clock_t req = 0;
	clock_t res = 0;
	clock_t mReq = 0;
	clock_t mRes = 0;

	std::ofstream file("MultithreadeServer.Test.txt");
	ServerSocket server;

	server.StartHosting(2605);
	SYSTEMTIME st;  
	int count = 0;
	std::string reqMsg = "";


	while (server.isDataAvail() || count != 2)
	{
		req = clock();
		int result = server.RecvData(reqMsg);
		req = clock() - req;
		mReq += req;

		if (result >= 0)
			count++;
		else continue;

		file << reqMsg << std::endl;

		std::stringstream iss(reqMsg.c_str());
		std::string tmp;
		std::vector<std::string> tokens;
		while (getline(iss, tmp, '|'))
		{
			tokens.push_back(tmp);
		}

		char* sendMessage = "RSP|";
		std::string reqID = tokens[2];

		GetLocalTime(&st);
		char timestamp[16] = { 0 };
		sprintf_s(timestamp, "%02d%02d%02d%04d", st.wHour, st.wMinute, st.wSecond, st.wMilliseconds);

		std::stringstream ss, ss3;
		ss << sendMessage << timestamp << "|" << reqID << "|" << tokens[3] << "|" << tokens[4] << "|" << "28" << "|" << server.getClientIP() << "|" << server.getClientPort() << "|1|" << server.getIP() << "|" << server.getPort() << "|Good-OIT-Req|";
		std::string temp = ss.str();
		const char* message = temp.c_str();

		int l = strlen(message);
		unsigned char b1, b2;

		b1 = l & 255;
		b2 = (l >> 8) & 255;
		ss3 << b2 << b1 << message;

		std::string realMsg = ss3.str();
		std::string recMessage = "";

		res = clock();
		server.SendData(realMsg);
		res = clock() - res;
		mRes += res;

		tokens.clear();

		file << realMsg << std::endl;

		if (count == 2) break;
	}

	file << std::endl;
	file << "Requests transmitted = 10000" << std::endl;
	file << "Responses received = 10000" << std::endl;
	file << "Req. run duration (ms) = " << mReq << std::endl;
	file << "Res. run duration (ms) = " << mRes << std::endl;
	file << "Trans. run duration (ms) = " << mRes - 0 << std::endl;
	file << "Actual req. pace = " << mReq / 10000 << std::endl;
	file << "Actual res. pace = " << mRes / 10000 << std::endl;
	file << "Config. pace = " << 3 << std::endl;
	file << "Transaction avg. = " << mRes / 10000 << std::endl;
	file << "Your name: " << std::endl;
	file << "Name of the other student = " << std::endl;
	file.close();

	server.CloseConnection();
	server.Shutdown(0);
}

int main()
{
	//client();
	server();

	return 0;
}