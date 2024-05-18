#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netdb.h>
#include <sys/socket.h>

#define PORT 80
#define BUFFER_SIZE 2048

void send_get_request(const char *hostname) {
    // Step 1: Create socket
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // Step 2: Get server address
    struct hostent *server = gethostbyname(hostname);
    if (server == NULL) {
        fprintf(stderr, "No such host\n");
        exit(EXIT_FAILURE);
    }

    struct sockaddr_in serv_addr;
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
    memcpy(&serv_addr.sin_addr.s_addr, server->h_addr, server->h_length);

    // Step 3: Connect to server
    if (connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        perror("Connection to server failed");
        exit(EXIT_FAILURE);
    }

    // Step 4: Send HTTP GET request
    char request[BUFFER_SIZE];
    snprintf(request, sizeof(request),
             "GET / HTTP/1.1\r\n"
             "Host: %s\r\n"
             "Connection: close\r\n\r\n", hostname);

    if (write(sockfd, request, strlen(request)) < 0) {
        perror("Failed to send request");
        exit(EXIT_FAILURE);
    }

    // Step 5: Open file to save response
    FILE *file = fopen("webpage.html", "w");
    if (!file) {
        perror("Failed to open file");
        exit(EXIT_FAILURE);
    }
    
    // Step 6: Read the response and save to file
    char response[BUFFER_SIZE];
    int bytes_read;
    while ((bytes_read = read(sockfd, response, sizeof(response) - 1)) > 0) {
        response[bytes_read] = '\0';
        fprintf(file, "%s", response);
    }

    // Step 7: Close the socket and the file
    close(sockfd);
    fclose(file);

    // Step 8: Open the saved file in the default web browser
    system("xdg-open webpage.html");
}

int main() {
    int choice;
    printf("Select a web server to access:\n");
    printf("1. Google\n");
    printf("2. UoN\n");
    printf("3. Bing\n");
    printf("4. Wikipedia\n");
    printf("Enter choice (1-4): ");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            send_get_request("www.google.com");
            break;
        case 2:
            send_get_request("www.uonbi.ac.ke");
            break;
        case 3:
            send_get_request("www.bing.com");
            break;
        case 4:
            send_get_request("www.wikipedia.com");
            break;
        default:
            printf("Invalid choice!\n");
            break;
    }

    return 0;
}
