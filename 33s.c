/*
 * ============================================================================
 Name : 33s.c
 Author :  yashswi chaturvedi
 Description : Write a program to communicate between two machines using socket.
 Date: 12th OCT, 2023.
============================================================================
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main() {
    int serverSocket, newSocket;
    struct sockaddr_in serverAddr, newAddr;
    socklen_t addrSize;
    char buffer[1024];

    // Create a socket
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket < 0) {
        perror("Socket creation failed");
        exit(1);
    }

    // Set up the server address structure
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(8080);
    serverAddr.sin_addr.s_addr = INADDR_ANY;

    // Bind the socket to the server address
    if (bind(serverSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) < 0) {
        perror("Binding failed");
        exit(1);
    }

    // Listen for incoming connections
    listen(serverSocket, 10);
    printf("Listening on port 8080...\n");

    // Accept a connection from a client
    addrSize = sizeof(newAddr);
    newSocket = accept(serverSocket, (struct sockaddr*)&newAddr, &addrSize);

    // Receive data from the client
    recv(newSocket, buffer, sizeof(buffer), 0);
    printf("Received from client: %s\n", buffer);

    // Send a response to the client
    char response[] = "Hello from the server";
    send(newSocket, response, sizeof(response), 0);
    printf("Response sent to client\n");

    // Close sockets
    close(newSocket);
    close(serverSocket);

    return 0;
}

