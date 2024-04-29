#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include "Client.h"
#include <exception>
#include <iostream>
#include <string>

Client::Client() {
	// Initialize Winsock
	if (WSAStartup(MAKEWORD(2, 2), &_wsaData) != 0) {
		std::cerr << "WSAStartup failed" << std::endl;
		throw std::exception(__FUNCTION__ " - WSAStartup");
	}

	// Create a socket
	_clientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	if (_clientSocket == INVALID_SOCKET) {
		std::cerr << "Socket creation failed" << std::endl;
		WSACleanup(); // Cleanup on failure
		throw std::exception(__FUNCTION__ " - socket");
	}

	std::cout << "Client initialized successfully" << std::endl;  // Add this line for debugging
}

Client::~Client()
{
	try
	{
		// the only use of the destructor should be for freeing 
		// resources that was allocated in the constructor
		closesocket(_clientSocket);
	}
	catch (...) {}
}


void Client::connectToServer(std::string serverIP, int port)
{

	struct sockaddr_in sa = { 0 };

	sa.sin_port = htons(port); // port that server will listen to
	sa.sin_family = AF_INET;   // must be AF_INET
	sa.sin_addr.s_addr =  inet_addr(serverIP.c_str());    // the IP of the server

	// the process will not continue until the server accepts the client
	int status = connect(_clientSocket, (struct sockaddr*)&sa, sizeof(sa));

	if (status == INVALID_SOCKET)
		throw std::exception("Cant connect to server");
}

void Client::startConversation()
{
	try
	{
		while (true)
		{
			//recive data from server
			char m[39];
			int bytesReceived = recv(_clientSocket, m, 38, 0);
			if (bytesReceived == SOCKET_ERROR || bytesReceived == 0) {
				throw std::runtime_error("Failed to receive data from server");
			}
			m[bytesReceived] = '\0';

			//check if server was closed 
			std::string test = m;
			if (test.find("server closed") != std::string::npos) {
				std::cout << "Server closed" << std::endl;
				break;
			}

			std::cout << "Message from server: " << m << std::endl;

			//get the message to send
			std::string s;
			std::cout << "send message to server:  " << std::endl;
			std::getline(std::cin, s);

			//send the message to the server
			int bytesSent = send(_clientSocket, s.c_str(), s.size(), 0);
			if (bytesSent == SOCKET_ERROR) {
				throw std::runtime_error("Failed to send data to server");
			}
		}
	}
	catch (const std::exception& e)
	{
		std::cout << "Error: " << e.what() << std::endl;
	}

	std::cout << "Socket closed" << std::endl;
}