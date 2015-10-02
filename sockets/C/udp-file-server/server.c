#include<sys/socket.h>
#include<arpa/inet.h>
#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/types.h>
#include<string.h>
#include<stdlib.h>

#define BUFSIZE 2000

 
int main()
{
 
  char buff[2000];
  char file_buffer[BUFSIZE];
  int sd,connfd;
  int s;
  socklen_t len;
  int last_read = 0;
  int next_read = 0;
  size_t fuel;
 
  struct sockaddr_in servaddr,cliaddr;
 
  sd = socket(AF_INET, SOCK_DGRAM, 0);
 
  if(sd==-1)
    {
      printf(" socket not created in server\n");
      exit(0);
    }
  else
    {
      printf("socket created in  server\n");
    }
 
  bzero(&servaddr, sizeof(servaddr));
 
  servaddr.sin_family = AF_INET;
  servaddr.sin_addr.s_addr = INADDR_ANY;
  servaddr.sin_port = htons(7802);
 
  if ( bind(sd, (struct sockaddr *)&servaddr, sizeof(servaddr)) != 0 )
    printf("Not binded\n");
  else
    printf("Binded to 7802\n");
 

 
  len=sizeof(cliaddr);
 
  recvfrom(sd,buff,1024,0, (struct sockaddr *)&cliaddr, &len);
 
  printf("%s\n",buff);
  /* */
  FILE *fp;
  fp=fopen(buff,"r");
  if(fp==NULL)
    {
      printf("file does not exist\n");
      return 1;
    }
 
  fseek(fp,0,SEEK_END);
  size_t file_size=ftell(fp);
  fseek(fp,0,SEEK_SET);
  printf("File size: %i\n", file_size);
  fuel = file_size;

  s = sprintf(buff, "%i\n", file_size);

  printf("send header: %s\n", buff);
  // send header
  // Format: "%i\n" where %i is the number of bytes sent after \n
  int snt;
  if ( (snt = sendto(sd, buff, s, 0, (struct sockaddr *)&cliaddr, len)) < 0)    {
    printf("error in sending the file\n");
    exit(1);
  }
  printf("send header bytes: %i\n", snt);
  while (1) {
    //printf("fuel: %i\n", fuel);
    if (fuel <= 0) {
      printf("fuel empty\n");
      break;
    }
    next_read = fuel < BUFSIZE ? fuel : BUFSIZE;
    if( (last_read = fread(file_buffer, 1, next_read, fp)) <=0)
      {
        printf("unable to copy file into buffer\n");
        exit(1);
      }

    if( next_read != last_read) {
      printf("expected these to be equal: %i, %i\n", next_read, last_read);
      exit(1);
    }

    fuel -= last_read;

    if (sendto(sd, file_buffer, last_read, 0, (struct sockaddr *)&cliaddr, len)<0)    {
      printf("error in sending the file\n");
      exit(1);
    }
    bzero(file_buffer,sizeof(file_buffer));
  }

  printf("close socket\n");
  /* */
  close(sd);
 
  return(0);
}
