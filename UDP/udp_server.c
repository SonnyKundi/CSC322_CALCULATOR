#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <math.h>

#define PORT 8080  // Define the port number for the server
#define EXIT_MSG "exit"  // Define the exit message

// Function to add two numbers
int add(int x, int y) {
    return x + y;
}

// Function to multiply two numbers
int multiply(int x, int y) {
    return x * y;
}

// Function to find the square of a number
int square(int x) {
    return x * x;
}

// Function to find the square root of a number
double squareRoot(int x) {
    if (x < 0) {
        return -1.0;
    }
    return sqrt(x);
}

int main() {
    int sockfd;
    struct sockaddr_in servaddr, cliaddr;

    // Create socket
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }

    memset(&servaddr, 0, sizeof(servaddr));  // Clear the server address structure
    memset(&cliaddr, 0, sizeof(cliaddr));  // Clear the client address structure

    // Fill server information
    servaddr.sin_family = AF_INET;  // IPv4
    servaddr.sin_port = htons(PORT);  // Server port
    servaddr.sin_addr.s_addr = INADDR_ANY;  // Any available interface

    // Bind the socket with the server address
    if (bind(sockfd, (const struct sockaddr *)&servaddr, sizeof(servaddr)) < 0) {
        perror("bind failed");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    int len, n;
    char buffer[1024];

    len = sizeof(cliaddr);  // Length of client address

    while (1) {
        // Receive message from client
        n = recvfrom(sockfd, buffer, sizeof(buffer), 0, (struct sockaddr *) &cliaddr, &len);
        buffer[n] = '\0';

        // Check for exit message
        if (strcmp(buffer, EXIT_MSG) == 0) {
            printf("Exit message received. Shutting down server...\n");
            break;
        }

        int choice, num1, num2;
        sscanf(buffer, "%d %d %d", &choice, &num1, &num2);  // Parse the received message

        double result;

        // Perform the appropriate operation based on the choice
        switch (choice) {
            case 1:
                result = add(num1, num2);
                snprintf(buffer, sizeof(buffer), "%d", (int)result);
                break;
            case 2:
                result = multiply(num1, num2);
                snprintf(buffer, sizeof(buffer), "%d", (int)result);
                break;
            case 3:
                result = square(num1);
                snprintf(buffer, sizeof(buffer), "%d", (int)result);
                break;
            case 4:
                result = squareRoot(num1);
                if (result == -1.0) {
                    snprintf(buffer, sizeof(buffer), "Cannot compute square root of a negative number!");
                } else {
                    snprintf(buffer, sizeof(buffer), "%.2f", result);
                }
                break;
            default:
                snprintf(buffer, sizeof(buffer), "Invalid choice!");
                break;
        }

        sendto(sockfd, buffer, strlen(buffer), 0, (const struct sockaddr *) &cliaddr, len);  // Send result back to client
    }

    close(sockfd);  // Close the socket
    return 0;
}
