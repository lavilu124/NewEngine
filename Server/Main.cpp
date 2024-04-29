#include <iostream>
#include "Server Code/Server.h"

int main() {
    Server NewServer;

    try {
        // Serve once
        NewServer.serve();


    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1; // Return a non-zero value to indicate an error
    }

    std::cout << "enter to exit";
    std::cin.get();

    return 0;
}
