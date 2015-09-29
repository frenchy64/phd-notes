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
  int num, fd;

  mknod(FIFO_NAME, S_IFIFO | 0666, 0);

  // BLOCK until other end is opened for reading
  printf("Waiting for readers...\n");
  fd = open(FIFO_NAME, O_WRONLY); // open write only named pipe
  printf("Got a reader\n");

  write(fd, "hello", 6);

  return 0;
}
