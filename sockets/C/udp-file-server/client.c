#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <sys/socket.h>
#include <resolv.h>
#include<netinet/in.h>
#include<sys/types.h>
#include<strings.h>
#include<string.h>
#include<unistd.h>
 

int main()
{
    char buff[2000];
    char header_buff[2000];
    int sockfd,connfd,len;
    int fuel;
    int header_fuel;
    size_t last_rec;
 
    struct sockaddr_in servaddr,cliaddr;
    socklen_t sl;

    // create socket in client side
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    if(sockfd==-1)
    {
      printf(" socket not created in client\n");
      exit(0);
    }
    else
    {
      printf("socket created in  client\n");
    }

    bzero(&servaddr, sizeof(servaddr));

    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = INADDR_ANY; // ANY address or use specific address
    servaddr.sin_port = htons(7802);  // Port address

    printf("Type ur  UDP client message\n");
    scanf("%s",buff);

    // send  msg to server

    printf("sending \n");
    sendto(sockfd, buff, strlen(buff), 0, (struct sockaddr *)&servaddr, sizeof(struct sockaddr));
    char file_buffer[2000];
    printf("created file_buffer\n");

    sl = sizeof(struct sockaddr);

    printf("received: \n");
    char new_file[2000]="copied";

    strcat(new_file,buff);

    // parse header
    if (recvfrom(sockfd, header_buff, 1999, 0, (struct sockaddr *)&servaddr, &sl) < 0) {
      printf("error reading header\n");
      exit(1);
    }

    int i;
    for(i = 0; i<2000; i++) {
      if (header_buff[i] == '\n') {
        header_buff[i+1] = '\0';
        break;
      }
      if (i == 1999) {
        printf("header too big\n");
        exit(1);
      }
    }
    sscanf(header_buff, "%i\n", &fuel);

    FILE *fp;
    fp=fopen(new_file,"w+");

    printf("receiving %i\n", fuel);
    while(1) {
      printf("fuel = %i\n", fuel);
      if (fuel <= 0) {
        break;
      }
      if ( (last_rec = recvfrom(sockfd, file_buffer, fuel<2000 ? fuel : 2000, 0, (struct sockaddr *)&servaddr, &sl)) < 0) {
        printf("error in receiving the file\n");
        exit(1);
      }
      fuel -= last_rec;
      if (last_rec == 0 && fuel != 0) {
        printf("error in receiving the file, zero bytes\n");
        exit(1);
      }
      if(fwrite(file_buffer, 1, last_rec, fp) < 0) {
        printf("error writting file\n");
        exit(1);
      }
    }
    printf("done\n");

    //close client side connection
    close(sockfd);

    return(0);
}
