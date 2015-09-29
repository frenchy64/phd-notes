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
  int fk;

  if(pipe(pfds) == -1) {
    perror("pipe");
    exit(1);
  }

  fk = fork();

  // fork a thread to spawn a child process. Send a
  // message to the parent process.
  if(fk == -1) {
    perror("Fork failed");
    exit(1);
  } else if (fk == 0) {
    printf("Parent process\n");
    // read message from process
    read(pfds[0], &buf, 5);

    printf("read from child: %s\n", buf);

  } else {
    printf("Child process\n");
    // write message to parent
    write(pfds[1], "Hell", 5);

  }
}
