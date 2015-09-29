#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<string.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>

#define FIFO_NAME "foobar"

int main(void) {
  char s[300];
  int num, fd;

  mknod(FIFO_NAME, S_IFIFO | 0666, 0);

  // BLOCK until other end is opened for writing
  printf("Waiting for writers...\n");
  fd = open(FIFO_NAME, O_RDONLY); // open read only named pipe
  printf("Got a write\n");

  num = read(fd, s, 6);
  s[num] = '\0';

  printf("Read: %s\n", s);

  return 0;
}
