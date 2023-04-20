#include <iostream>
#include <string>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>

// Function to display errors and exit the program
void error(const std::string &msg) {
    std::cerr << msg << std::endl;
    exit(1);
}

int main(int argc, char *argv[]) {
    if (argc < 3) {
        error("Usage: ./udp_client <server_address> <port_number>");
    }

    // Get server address and port from command line arguments
    const char *server_address = argv[1];
    int port_number = std::stoi(argv[2]);

    // Create a UDP socket
    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        error("Error creating socket");
    }

    // Set up the server address struct
    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port_number);
    if (inet_pton(AF_INET, server_address, &server_addr.sin_addr) <= 0) {
        error("Invalid server address");
    }

    // Send a message to the server
    std::string message = "Hello from the client!";
    if (sendto(sockfd, message.c_str(), message.length(), 0, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        error("Error sending message");
    }

    // Close the socket and exit the program
    close(sockfd);
    return 0;
}