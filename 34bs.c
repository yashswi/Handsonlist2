/*
 * ============================================================================
 Name : 34bs.c
 Author : yashswi chaturvedi
 Description : Write a program to create a concurrent server.
 b. use pthread_create
 Date: 12th OCT, 2023.
============================================================================
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <pthread.h>

#define PORT 12345
#define MAX_BUFFER_SIZE 1024

void *handle_client(void *arg) {
    int client_socket = *((int *)arg);
    char buffer[MAX_BUFFER_SIZE];
    int bytes_received;

    while (1) {
        bytes_received = recv(client_socket, buffer, sizeof(buffer), 0);
        if (bytes_received <= 0) {
            break;
        }
        buffer[bytes_received] = '\0';
        printf("Received: %s", buffer);

        // Handle client request here and send a response back if needed.

        send(client_socket, buffer, strlen(buffer), 0);
    }

    close(client_socket);
    free(arg);
    return NULL;
}

int main() {
    int server_socket, client_socket;
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_addr_len = sizeof(client_addr);
    pthread_t tid;
    int *new_client_socket;

    // Create socket
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket == -1) {
        perror("Error creating socket");
        exit(EXIT_FAILURE);
    }

    // Prepare the server address structure
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    // Bind the socket to the server address
    if (bind(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
        perror("Error binding socket");
        exit(EXIT_FAILURE);
    }

    // Listen for incoming connections
    if (listen(server_socket, 5) == -1) {
        perror("Error listening");
        exit(EXIT_FAILURE);
    }

    printf("Server is listening on port %d...\n", PORT);

    while (1) {
        // Accept incoming connections
        client_socket = accept(server_socket, (struct sockaddr *)&client_addr, &client_addr_len);
        if (client_socket == -1) {
            perror("Error accepting connection");
            continue;
        }

        // Create a new thread to handle the client
        new_client_socket = (int *)malloc(sizeof(int));
        *new_client_socket = client_socket;
        if (pthread_create(&tid, NULL, handle_client, new_client_socket) != 0) {
            perror("Error creating thread");
            free(new_client_socket);
            close(client_socket);
        }
    }

    // Close the server socket (this part is typically unreachable)
    close(server_socket);

    return 0;
}


