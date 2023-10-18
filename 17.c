/*
 * ============================================================================
 Name : 17.c
 Author :  yashswi chaturvedi
 Description : Write a program to execute ls -l | wc.
a. use dup
b. use dup2
c. use fcntl
 Date: 10th OCT, 2023.
============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
int main() {
    int pipe_fd[2];

    if (pipe(pipe_fd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    pid_t child_pid = fork();

    if (child_pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (child_pid == 0) {  
        close(pipe_fd[0]);  

	fcntl(pipe_fd[1], F_SETFD, FD_CLOEXEC);  
        dup2(pipe_fd[1], STDOUT_FILENO);	
        
	close(pipe_fd[1]);  

        execlp("ls", "ls", "-l", NULL);
        perror("execlp");
        exit(EXIT_FAILURE);
    } else { 
        close(pipe_fd[1]); 
        
	fcntl(pipe_fd[0], F_SETFD, FD_CLOEXEC);  
        dup2(pipe_fd[0], STDIN_FILENO);
        
	close(pipe_fd[0]);  

        execlp("wc", "wc", NULL);  
        perror("execlp");
        exit(EXIT_FAILURE);
    }

    return 0;
}

