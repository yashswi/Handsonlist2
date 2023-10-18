/*
 * ============================================================================
 Name : 33.c
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
    int clientSocket;
    struct sockaddr_in serverAddr;
    char buffer[1024];

    // Create a socket
    clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket < 0) {
        perror("Socket creation failed");
        exit(1);
    }

    // Set up the server address structure
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(8080);
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1"); 

    // Connect to the server
    if (connect(clientSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) < 0) {
        perror("Connection failed");
        exit(1);
    }

    // Send data to the server
    char message[] = "Hello from the client";
    send(clientSocket, message, sizeof(message), 0);
    printf("Message sent to server\n");

    // Receive a response from the server
    recv(clientSocket, buffer, sizeof(buffer), 0);
    printf("Received from server: \n");

    // Close the socket
    close(clientSocket);

    return 0;
}

