#include<stdio.h>
#include<unistd.h>

int main(){
  int fd[2];
  int status;
  char buff[35];
  int r, w;
  if((status=pipe(fd)) == -1) printf("\nError creating pipe!!");
  else{
	//writing to the pipe
	w = write(fd[1], "Hello World written to the pipe!!",33);
	if(w==-1) printf("\n Unable to write to the pipe");
	else
	{
		//reading for pipe
		printf("\n Reading...");
		r = read(fd[0], &buff, w);
		if(r==-1) printf("\n Unable to read!!");
		else printf("\nThe pipe read : %s", buff);
	} 
  }
  return 0;
}
