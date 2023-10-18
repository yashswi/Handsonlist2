/*
============================================================================
Name : 18.c
Author : yashswi chaturvedi
Description : Write a program to find out total number of directories on the pwd.execute ls -l | grep ^d | wc ? Use only dup2.
Date: 10-october-2023
============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    int pipe_fd[2];
    pid_t pid;

    // Create a pipe
    if (pipe(pipe_fd) == -1) {
        perror("Pipe creation failed");
        exit(EXIT_FAILURE);
    }

    // Fork a child process
    pid = fork();

    if (pid == -1) {
        perror("Fork failed");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) {
        // Child process
        close(pipe_fd[0]); // Close the read end of the pipe
        // Redirect stdout to the write end of the pipe
        dup2(pipe_fd[1], STDOUT_FILENO);
        close(pipe_fd[1]); // Close the write end of the pipe

        // Execute the 'ls -l' command
        execlp("ls", "ls", "-l", NULL);
        perror("execlp");
        exit(EXIT_FAILURE);
    } else {
        // Parent process
        close(pipe_fd[1]); // Close the write end of the pipe
        // Redirect stdin to the read end of the pipe
        dup2(pipe_fd[0], STDIN_FILENO);
        close(pipe_fd[0]); // Close the read end of the pipe

        // Create a pipe for the second 'grep' process
        int pipe_fd2[2];
        if (pipe(pipe_fd2) == -1) {
            perror("Second pipe creation failed");
            exit(EXIT_FAILURE);
        }

        pid_t pid2 = fork();

        if (pid2 == -1) {
            perror("Fork (second) failed");
            exit(EXIT_FAILURE);
        }

        if (pid2 == 0) {
            // Child process (second)
            close(pipe_fd2[0]); // Close the read end of the second pipe
            // Redirect stdout to the write end of the second pipe
            dup2(pipe_fd2[1], STDOUT_FILENO);
            close(pipe_fd2[1]); // Close the write end of the second pipe

            // Execute the 'grep ^d' command
            execlp("grep", "grep", "^d", NULL);
            perror("execlp (second)");
            exit(EXIT_FAILURE);
        } else {
            // Parent process (first)
            close(pipe_fd2[1]); // Close the write end of the second pipe
            // Redirect stdin to the read end of the second pipe
            dup2(pipe_fd2[0], STDIN_FILENO);
            close(pipe_fd2[0]); // Close the read end of the second pipe

            // Wait for the second 'grep' process to finish
            wait(NULL);

            char buffer[1024];
            int directoryCount = 0;

            // Read and count the lines produced by 'grep'
            while (fgets(buffer, sizeof(buffer), stdin) != NULL) {
                directoryCount++;
            }

            if (directoryCount == 0) {
                // No directories found
                printf("No directories found\n");
            } else {
                // Directories found, print the count
                printf("Number of directories: %d\n", directoryCount);
            }
        }
    }

    return 0;
}

