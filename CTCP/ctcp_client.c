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
    int sock = 0;
    struct sockaddr_in serv_addr;
    char buffer[1024] = {0};

    // Create socket
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("Socket creation error\n");
        return -1;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    // Convert IPv4 and IPv6 addresses from text to binary form
    if (inet_pton(AF_INET, "192.168.0.103", &serv_addr.sin_addr) <= 0) {  // Use server's IP address here
        printf("Invalid address/ Address not supported\n");
        return -1;
    }

    // Connect to server
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        printf("Connection Failed\n");
        return -1;
    }

    while (1) {
        printMenu();
        int choice = getChoice();

        // Exit condition
        if (choice == 5) {
            strcpy(buffer, EXIT_MSG);
            send(sock, buffer, strlen(buffer), 0);
            printf("Exit message sent to server...\n");
            break;
        }

        int num1, num2;
        double result;

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
        send(sock, buffer, strlen(buffer), 0);
        printf("Operation sent to server...\n");

        // Receive result from server
        int valread = read(sock, buffer, 1024);
        buffer[valread] = '\0';
        printf("From Server: Result: %s\n", buffer);
    }

    close(sock);  // Close the socket
    return 0;
}
