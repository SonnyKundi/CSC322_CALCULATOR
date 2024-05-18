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
    int server_fd, new_socket;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    char buffer[1024] = {0};

    // Create socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    // Attaching socket to the port 8080
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt))) {
        perror("setsockopt");
        close(server_fd);
        exit(EXIT_FAILURE);
    }
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    // Bind the socket to the port
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("bind failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    // Listen for incoming connections
    if (listen(server_fd, 3) < 0) {
        perror("listen");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    // Accept incoming connection
    if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
        perror("accept");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    while (1) {
        int valread = read(new_socket, buffer, 1024);
        buffer[valread] = '\0';

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

        send(new_socket, buffer, strlen(buffer), 0);  // Send result back to client
    }

    close(new_socket);  // Close the client socket
    close(server_fd);  // Close the server socket
    return 0;
}
