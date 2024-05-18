#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080  // Define the port number for the server
#define EXIT_MSG "exit"  // Define the exit message

// Function to print the menu options
void printMenu() {
    printf("Calculator:\n");
    printf("1. Add Two Numbers\n");
    printf("2. Multiply Two Numbers\n");
    printf("3. Square a Number\n");
    printf("4. Square Root of a Number\n");
    printf("5. Exit\n");
}

// Function to get the user's menu choice
int getChoice() {
    int choice;
    printf("Enter your choice: ");
    scanf("%d", &choice);
    return choice;
}

// Function to get a number from the user
int getNumber() {
    int num;
    printf("Enter number: ");
    scanf("%d", &num);
    return num;
}

int main() {
    int sockfd;
    struct sockaddr_in servaddr;  // Server address structure
    char buffer[1024];  // Buffer to hold data to send/receive
    char *server_ip = "192.168.0.103"; // Server's IP address

    // Create a UDP socket
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }

    memset(&servaddr, 0, sizeof(servaddr));  // Clear the server address structure

    // Fill server information
    servaddr.sin_family = AF_INET;  // IPv4
    servaddr.sin_port = htons(PORT);  // Server port

    // Convert IPv4 and IPv6 addresses from text to binary form
    if (inet_pton(AF_INET, server_ip, &servaddr.sin_addr) <= 0) {
        printf("Invalid address/ Address not supported\n");
        return -1;
    }

    while (1) {
        printMenu();  // Display the menu options
        int choice = getChoice();  // Get the user's choice

        // Exit condition
        if (choice == 5) {
            strcpy(buffer, EXIT_MSG);
            sendto(sockfd, buffer, strlen(buffer), 0, (const struct sockaddr *) &servaddr, sizeof(servaddr));
            printf("Exit message sent to server...\n");
            break;
        }

        int num1, num2;

        // Get numbers based on the choice
        switch (choice) {
            case 1:
            case 2:
                printf("Enter two numbers:\n");
                num1 = getNumber();
                num2 = getNumber();
                sprintf(buffer, "%d %d %d", choice, num1, num2);
                break;
            case 3:
            case 4:
                printf("Enter a number:\n");
                num1 = getNumber();
                sprintf(buffer, "%d %d", choice, num1);
                break;
            default:
                printf("Invalid choice!\n");
                continue;
        }

        // Send operation and numbers to server
        sendto(sockfd, buffer, strlen(buffer), 0, (const struct sockaddr *) &servaddr, sizeof(servaddr));
        printf("Operation sent to server...\n");

        // Receive result from server
        int n = recvfrom(sockfd, buffer, sizeof(buffer), 0, NULL, NULL);
        buffer[n] = '\0';
        printf("From Server: Result: %s\n", buffer);
    }

    close(sockfd);  // Close the socket
    return 0;
}
