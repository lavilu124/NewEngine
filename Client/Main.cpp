#include <iostream>
#include "Client Code/Client.h"

int main(){
    Client NewClient;

    try {
		//get ip address
        std::string ip; 
        std::cout << "enter the ip";
		std::getline(std::cin, ip);

		//connect to server
        NewClient.connectToServer(ip, 13780);

		//start conversation
        NewClient.startConversation();
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1; 
    }

    std::cout << "enter to exit";
	std::cin.get();
    return 0;
}
