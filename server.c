#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>  //inode access and modification times
#include <arpa/inet.h>  //Functions for manipulating numeric IP addresses (part of Berkeley sockets)

#define SERVER_IP "127.0.0.1"  // Change this to the desired IP address
#define SERVER_PORT 12345      // Change this to the desired port number
#define BUFFER_SIZE 1024

int main() {
    //create a socket object
    int sockfd;  
    struct sockaddr_in serverAddr, clientAddr;
    char buffer[BUFFER_SIZE];
    socklen_t addr_size;   

    // Create UDP socket
    sockfd = socket(PF_INET, SOCK_DGRAM, 0);  //SOCK_DGRAM is a UDP package
    if (sockfd < 0) {
        perror("Error creating UDP socket");
        exit(1);
    }

    // Configure server address
    memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = inet_addr(SERVER_IP);
    serverAddr.sin_port = htons(SERVER_PORT);

    // Bind socket to address
    if (bind(sockfd, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) < 0) {
        perror("Error in bind");
        close(sockfd);
        exit(1);
    }

    printf("Server listening on %s:%d\n", SERVER_IP, SERVER_PORT);

    while (1) {
        // Receive message from client
        addr_size = sizeof(clientAddr);
        ssize_t dataSize = recvfrom(sockfd, buffer, BUFFER_SIZE, 0, (struct sockaddr *)&clientAddr, &addr_size);

        // Echo back the received message
        if (dataSize > 0) {
            printf("Received message from client: %s\n", buffer);
            sendto(sockfd, buffer, dataSize, 0, (struct sockaddr *)&clientAddr, addr_size);
        }
        // Clear the data buffer after receiving message from the client, so that the next time the client sends a message won't be disturb
        memset(buffer, 0, BUFFER_SIZE);
    }

    close(sockfd);
    return 0;
}
