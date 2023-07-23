#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define SERVER_IP "127.0.0.1"  // Change this to the server IP address
#define SERVER_PORT 12345      // Change this to the server port number
#define BUFFER_SIZE 1024
#define MAX_RETRY 10

unsigned int exponential_backoff(unsigned int retry, unsigned int max_retry) {
    unsigned int base = 500;  // base in milliseconds
    unsigned int multiplier = 2;
    unsigned int wait_interval = base * (1 << (retry > 6 ? 6 : retry)); // Limit wait_interval to 8 seconds
    return wait_interval > base ? base : wait_interval;
}

int main() {
    int sockfd;
    struct sockaddr_in serverAddr;
    char buffer[BUFFER_SIZE];
    socklen_t addr_size;
    int retry = 0;

    // Create UDP socket
    sockfd = socket(PF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        perror("Error in socket");
        exit(1);
    }

    // Configure server address
    memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = inet_addr(SERVER_IP);
    serverAddr.sin_port = htons(SERVER_PORT);

    // Clear the data buffer before receiving the user message
    memset(buffer, 0, BUFFER_SIZE);

    // User input for the message content
    printf("Enter the message to send to the server: ");
    fgets(buffer, BUFFER_SIZE, stdin);
    buffer[strcspn(buffer, "\n")] = '\0';  // Remove the newline character from the input

    // Send UDP message with exponential backoff retries
    while (retry <= MAX_RETRY) {
        printf("Sending message to server: Attempt %d\n", retry + 1);
        //sprintf(buffer, "Hello, server! Attempt %d", retry + 1);

        sendto(sockfd, buffer, strlen(buffer), 0, (struct sockaddr *)&serverAddr, sizeof(serverAddr));

        addr_size = sizeof(serverAddr);
        ssize_t dataSize = recvfrom(sockfd, buffer, BUFFER_SIZE, 0, (struct sockaddr *)&serverAddr, &addr_size);

        if (dataSize > 0) {
            buffer[dataSize] = '\0';
            printf("Received echo message: %s\n", buffer);
            close(sockfd);
            return 0; // Exit with code 0 on successful echo received
        }

        // Wait for the next retry
        unsigned int wait_time = exponential_backoff(retry, MAX_RETRY);
        sleep(wait_time / 1000);  // Convert milliseconds to seconds
        retry++;
    }

    printf("Max retries reached. Exiting.\n");
    close(sockfd);
    return 1; // Exit with code 1 if max-retry reached
}
