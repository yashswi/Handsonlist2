#include<stdio.h>
#include<unistd.h>
#include<sys/wait.h>

int main()
{
  int fd[2]; //pipe has two fds
  //fd[0] read end
  //fd[1] write end of the pipe

  pipe(fd); //pipe stores its file descriptors in the two integers, fd[0] & fd[1]
  int num;
  if(!fork())
  {
	//child process
        printf("Hi i am child\n");
	//since file descriptors are also inherited and we dont want to write, we must close the write end in the child process
	close(fd[1]);

        //makes the parent to execute first
        //sleep(5);
	read(fd[0], &num, sizeof(int));
	printf("Msg fro parent is : %d\n", num);
	close(fd[0]);
  }
  else
  {     printf("Hi i am Parent\n");
	//parent process
	close(fd[0]); //close parents read descriptor as it is not going to read

	//printf("Enter a number: \n");
	//scanf("%d", &num);
	num = 5;
	write(fd[1], &num, sizeof(int));

	//waits for child process to exit first
	wait(0);
	close(fd[1]);
  }

  return 0;
}
