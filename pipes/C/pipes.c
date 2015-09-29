#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<unistd.h>

#define BUFLEN 30

int main(void) {
  // pfds[0] contains read file descriptor for pipe
  // pfds[1] contains write file descriptor for pipe
  int pfds[2];
  char buf[BUFLEN];

  if(pipe(pfds) == -1) {
    perror("pipe");
    exit(1);
  }

  printf("writing to file descriptor #%d\n", pfds[1]);
  // send 5 bytes to write side of pipe
  write(pfds[1], "tsst", 5);
  printf("reading from file descriptor\n", pfds[0]);
  // read 5 bytes from read side of pipe
  read(pfds[0], buf, 5);

  printf("read: %s\n", buf);
}
