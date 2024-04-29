#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include "Server.h"
#include <exception>
#include <iostream>
#include <string>
#include <thread>


Server::Server()
{	
	// Initialize Winsock
	if (WSAStartup(MAKEWORD(2, 2), &_wsaData) != 0) {
		std::cerr << "WSAStartup failed" << std::endl;
		throw std::exception(__FUNCTION__ " - WSAStartup");
	}

	this->port = 13780;
	// this server use TCP. that why SOCK_STREAM & IPPROTO_TCP
	// if the server use UDP we will use: SOCK_DGRAM & IPPROTO_UDP
	_serverSocket = socket(AF_INET,  SOCK_STREAM,  IPPROTO_TCP); 

	if (_serverSocket == INVALID_SOCKET)
		throw std::exception(__FUNCTION__ " - socket");
}

Server::~Server()
{
	try
	{
		// the only use of the destructor should be for freeing 
		// resources that was allocated in the constructor
		closesocket(_serverSocket);
	}
	catch (...) {}
}

void Server::serve()
{
	struct sockaddr_in sa = { 0 };
	
	sa.sin_port = htons(port); // port that server will listen for
	sa.sin_family = AF_INET;   // must be AF_INET
	sa.sin_addr.s_addr = INADDR_ANY;    // when there are few ip's for the machine. We will use always "INADDR_ANY"

	// Connects between the socket and the configuration (port and etc..)
	if (bind(_serverSocket, (struct sockaddr*)&sa, sizeof(sa)) == SOCKET_ERROR)
		throw std::exception(__FUNCTION__ " - bind");
	
	// Start listening for incoming requests of clients
	if (listen(_serverSocket, SOMAXCONN) == SOCKET_ERROR)
		throw std::exception(__FUNCTION__ " - listen");
	std::cout << "Listening on port " << port << std::endl;

	bool ranClient = false;
	while (!ranClient)
	{
		std::cout << "Waiting for client connection request" << std::endl;
		ranClient = acceptClient();
	}
}


bool Server::acceptClient()
{

	// this accepts the client and create a specific socket from server to this client
	// the process will not continue until a client connects to the server
	SOCKET client_socket = accept(_serverSocket, NULL, NULL);
	if (client_socket == INVALID_SOCKET) {
		throw std::exception(__FUNCTION__);
		return false;
	}

	std::cout << "Client accepted. Server and client can speak" << std::endl;
	// the function that handle the conversation with the client
	clientHandler(client_socket);
	return true;
}


void Server::clientHandler(SOCKET clientSocket)
{
	try
	{
		while (true) {
			//get the message to send
			std::string s;
			std::cout << "send message to client (enter 'e' to exit):  " << std::endl;
			std::getline(std::cin, s);

			//check for exit
			if (s == "e") {
				s = "server closed";
				send(clientSocket, s.c_str(), s.size(), 0);
				break;
			}

			//send the message to the client
			int bytesSent = send(clientSocket, s.c_str(), s.size(), 0);
			if (bytesSent == SOCKET_ERROR) {
				throw std::runtime_error("Failed to send data to client");
			}

			//recv the message from the client
			char m[39];
			int bytesReceived = recv(clientSocket, m, 38, 0);
			if (bytesReceived == SOCKET_ERROR || bytesReceived == 0) {
				throw std::runtime_error("Failed to receive data from client");
			}
			m[bytesReceived] = '\0';
			std::cout << "Message from client: " << m << std::endl;
		}
	}
	catch (const std::exception& e)
	{
		std::cout << "Error: " << e.what() << std::endl;
	}

	closesocket(clientSocket);
}


