#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <math.h>

#define PORT 8080  // Define the port number for the server
#define EXIT_MSG "exit"  // Define the exit message

int server_running = 1;  // Global variable to control server loop

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

// Thread function to handle client requests
void* handle_client(void* arg) {
    int sockfd = *((int*)arg);  // Get the socket file descriptor
    struct sockaddr_in cliaddr;  // Client address structure
    char buffer[1024];  // Buffer to hold received data
    socklen_t len = sizeof(cliaddr);  // Length of the client address
    int n;  // Number of bytes received

    while (server_running) {
        // Receive a message from the client
        n = recvfrom(sockfd, buffer, sizeof(buffer), 0, (struct sockaddr *)&cliaddr, &len);
        buffer[n] = '\0';  // Null-terminate the received data

        // Check for exit message
        if (strcmp(buffer, EXIT_MSG) == 0) {
            printf("Exit message received. Shutting down server...\n");
            server_running = 0;
            break;
        }

        int choice, num1, num2;
        // Parse the received message to extract the operation and numbers
        sscanf(buffer, "%d %d %d", &choice, &num1, &num2);

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

        // Send the result back to the client
        sendto(sockfd, buffer, strlen(buffer), 0, (const struct sockaddr *)&cliaddr, len);
    }

    close(sockfd);  // Close the socket
    pthread_exit(NULL);  // Exit the thread
}

int main() {
    int sockfd;
    struct sockaddr_in servaddr;  // Server address structure
    pthread_t tid;  // Thread identifier

    // Create a UDP socket
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }

    memset(&servaddr, 0, sizeof(servaddr));  // Clear the server address structure

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

    // Create a thread to handle client requests
    pthread_create(&tid, NULL, handle_client, (void*)&sockfd);
    pthread_join(tid, NULL);  // Wait for the thread to finish

    close(sockfd);  // Close the socket
    return 0;
}
