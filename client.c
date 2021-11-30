#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#define SIZE 1024

void write_file(int sockfd){
  int n;
  FILE *fp;
  char *filename = "recv.txt";
  char buffer[SIZE];

  fp = fopen(filename, "w");
  while (1) {
    n = recv(sockfd, buffer, SIZE, 0);
    if (n <= 0){
      break;
      return;
    }
    fprintf(fp, "%s", buffer);
    printf("%s\n", buffer);
    bzero(buffer, SIZE);
  }
  return;
}
int main(int agrc,char *argv[]){
  int e;char fname[100];

  int sockfd;
  struct sockaddr_in server_addr;
  FILE *fp;
  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if(sockfd < 0) {
    perror(".....Error in socket......");
    exit(1);
  }
  printf("...Client socket created successfully...\n");
  server_addr.sin_family = AF_INET;
  server_addr.sin_port = atoi(argv[2]);
  server_addr.sin_addr.s_addr = inet_addr(argv[1]);

  e = connect(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr));
  if(e == -1) {
    perror("///Error in socket///");
    exit(1);
  }
	printf("->Connected to Server---\n");
printf("enter the file name you want to get from server :");
scanf("%s",fname);
send(sockfd,&fname,sizeof(fname),0);
printf("->File name succesfully sent to server<-\n");
  
  write_file(sockfd);
  printf("Data written in the file(recv.txt)successfully.\n");
  printf("...Closing the connection...\n");
 close(sockfd);

  return 0;
}

