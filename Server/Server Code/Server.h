#pragma once

#include <WinSock2.h>
#include <Windows.h>
#include <string>
#pragma comment(lib, "ws2_32.lib")

class Server
{
public:
	Server();
	~Server();
	void serve();

private:

	bool acceptClient();
	void clientHandler(SOCKET clientSocket);

	SOCKET _serverSocket;

	WSADATA _wsaData;

	int port;

};

