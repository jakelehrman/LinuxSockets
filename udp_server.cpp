#include <iostream>
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
    if (argc < 2) {
        error("Usage: ./udp_server <port_number>");
    }

    // Get the port number from command line arguments
    int port_number = std::stoi(argv[1]);

    // Create a UDP socket
    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        error("Error creating socket");
    }

    // Set up the server address struct
    struct sockaddr_in server_addr, client_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port_number);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    // Bind the socket to the server address
    if (bind(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        error("Error binding socket");
    }

    // Receive a message from the client
    char buffer[1024];
    socklen_t client_addr_len = sizeof(client_addr);
    int recv_len = recvfrom(sockfd, buffer, sizeof(buffer), 0, (struct sockaddr *)&client_addr, &client_addr_len);
    if (recv_len < 0) {
        error("Error receiving message");
    }
    buffer[recv_len] = '\0';

    // Print the received message
    std::cout << "Received message from client: " << buffer << std::endl;

    // Close the socket and exit the program
    close(sockfd);
    return 0;
}