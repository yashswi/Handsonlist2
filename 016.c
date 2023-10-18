/*
============================================================================
Name : 16.c
Author yashswi chaturvedi
Description : Write a program to send and receive data from parent to child vice versa. Use two way
communication.
Date: 1st oct, 2023.
============================================================================
*/
#include<sys/wait.h>
#include<unistd.h>
#include<stdio.h>

int main()
{
  //flow->
  //pass a number to one process -> some function on the number -> return the result to the process

  //we don't want to do reading and writing on the same pipe
  int p1[2]; //child to parent
  int p2[2]; //parent to child

  if(pipe(p1)==-1) printf("\n Unable to create pipe from child to parent!!");
  if(pipe(p2)==-1) printf("\n Unable to create pipe from parent to child!!"); 
  
  if(!fork())
  {
	//child process
	close(p1[0]); //not reading from pipe made to send data to parent
	close(p2[1]); //not writing to pipe made to receive data from parent

	int num;
	if(read(p2[0], &num, sizeof(num)) == -1) printf("\nUnable to read (data from parent process)");
	printf("\nReceived %d from parent\n", num);
	//sqaurig the number
	num*=num;
	if(write(p1[1], &num, sizeof(num)) == -1) printf("\nUnable to send the result");
	printf("\nSent the result to the parent process\n");

	close(p1[1]);
        close(p2[0]);
  }
  else
  {
	//parent
	close(p1[1]);
	close(p2[0]);

	//lets pass 5 to the child
	int res = 5;
	if(write(p2[1], &res, sizeof(int))==-1) printf("\nUnable to write (send data to child)");
	//try commenting the below else statement!!
	else printf("\nSuccessfully sent %d to child process for further processing\n", res);

	
	if(read(p1[0], &res, sizeof(res)) == -1) printf("\nUnable to read result!!!");
	else printf("\nProcessed Result is %d\n", res);

	wait(0);//wait to child process

	close(p1[0]);
        close(p2[1]);

  }
  return 0;
}
