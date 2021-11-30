#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include<unistd.h>
#define SIZE 1024
void send_file(FILE *fp, int sockfd){
  int n;
  char data[SIZE] = {0};

  while(fgets(data, SIZE, fp) != NULL) {
    if (send(sockfd, data, sizeof(data), 0) == -1) {
      perror("....Error in sending file....");
      exit(1);
    }
    bzero(data, SIZE);
  }
}
int main(int argc,char *argv[]){
  int e;FILE *fp;char fname[100];

  int sockfd, new_sock;
  struct sockaddr_in server_addr, new_addr;
  socklen_t addr_size;
  char buffer[SIZE];
  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if(sockfd < 0) {
    perror("...Error in socket...");
    exit(1);
  }
  printf("...Server socket created successfully...\n");

  server_addr.sin_family = AF_INET;
  server_addr.sin_port = atoi(argv[1]);
  server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

  e = bind(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr));
  if(e < 0) {
    perror("->Error in bind<-");
    exit(1);
  }
  printf("...Binding successfull...\n");

  if(listen(sockfd, 10) == 0){
		printf("->Listening....\n");
	}else{
		perror("Error in listening");
    exit(1);
	}
  addr_size = sizeof(new_addr);
  new_sock = accept(sockfd, (struct sockaddr*)&new_addr, &addr_size);
  recv(new_sock,&fname,sizeof(fname),0);
	if(strcmp(fname,"send.txt")==0)
	    fp=fopen("/home/ubuntu/environment/RA1911003010799/exp8/server/send.txt","r");
  send_file(fp,new_sock);
  printf("-->File data sent successfully<--\n");

	printf("....Closing the connection....\n");
  close(sockfd);
  return 0;
}
