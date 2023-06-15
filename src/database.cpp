//TO RUN: 
// g++ database.cpp
// ./a.out




//the required header files
#include <iostream>
#include <string>
#include <cstdlib>
#include <cstring>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netinet/in.h>


std::string GetLocalIpAddress() {
    char hostname[256];
    //if gethostname returns error, function will return empty string
    if (gethostname(hostname, sizeof(hostname)) != 0) {
        perror("gethostname");
        return "";
    }

    //hints is a struct of addrinfo, res and p are pointers to the struct
    struct addrinfo hints, *res, *p;
    //sets all bytes of hints to 0, initializing it
    std::memset(&hints, 0, sizeof(hints));
    //setting the fields of struct, AF_INET means IPv4, SOCK_STREAM means stream socket
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;

    //this function gets address information, failure will return perror and return an empty string
    if (getaddrinfo(hostname, nullptr, &hints, &res) != 0) {
        perror("getaddrinfo");
        return "";
    }

    std::string ipAddress;

    //loop through a network of addresses res
    for (p = res; p != nullptr; p = p->ai_next) {
        //changes the struct type of p
        struct sockaddr_in* addr = reinterpret_cast<struct sockaddr_in*>(p->ai_addr);
        char buffer[INET_ADDRSTRLEN];
        //converts binary address to string representation and puts it into buffer
        inet_ntop(AF_INET, &(addr->sin_addr), buffer, INET_ADDRSTRLEN);
        std::string currentIpAddress(buffer);

        // Ignores the loopback address, breaks the loop once ignored
        if (currentIpAddress != "127.0.0.1") {
            ipAddress = currentIpAddress;
            break;
        }
    }

    freeaddrinfo(res);
    return ipAddress;
}

int main() {
    //runs the getLocalIpAddress function and stores into localIpAddress
    std::string localIpAddress = GetLocalIpAddress();
    std::cout << "Local IP Address: " << localIpAddress << std::endl;

    // Create a socket
    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket < 0) {
        std::cerr << "Error creating socket" << std::endl;
        return 1;
    }

    // Bind the socket to a specific address and port
    sockaddr_in serverAddress;
    memset(&serverAddress, 0, sizeof(serverAddress));
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = INADDR_ANY; // Accept connections from any IP address
    serverAddress.sin_port = htons(1030); // Choose a suitable port number
    if (bind(serverSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) < 0) {
        std::cerr << "Error binding socket" << std::endl;
        return 1;
    }

    // Listen for incoming connections
    listen(serverSocket, 1);

    // Accept a client connection
    int clientSocket = accept(serverSocket, nullptr, nullptr);
    if (clientSocket < 0) {
        std::cerr << "Error accepting client connection" << std::endl;
        return 1;
    }

    // Data to be sent
    std::string message = "Hello, Python! BYE PYTHON!";

    // Send the string data to the client followed by a delimiter
    if (send(clientSocket, message.c_str(), message.size(), 0) < 0) {
        std::cerr << "Error sending message data" << std::endl;
        return 1;
    }

    // Send a delimiter to indicate the end of the string
    const char delimiter = '\n';
    if (send(clientSocket, &delimiter, sizeof(delimiter), 0) < 0) {
        std::cerr << "Error sending delimiter" << std::endl;
        return 1;
    }

    // Close the sockets
    close(clientSocket);
    close(serverSocket);

    return 0;
}



