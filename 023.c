/*
============================================================================
Name : 23.c
Author : yashswi chaturvedi
Description : Write a program to print the maximum number of files can be opened within a process and
size of a pipe (circular buffer).
Date: 1st oct, 2023.
============================================================================
*/

#include<unistd.h>
#include<stdio.h>
int main()
{
  long PIPE_BUF, OPEN_MAX;
  PIPE_BUF = pathconf(".", _PC_PIPE_BUF);
  OPEN_MAX = sysconf(_SC_OPEN_MAX);

  printf("Size of pipe = %ld\t Max number of files=%ld\n", PIPE_BUF, OPEN_MAX);

  return 0;
}

