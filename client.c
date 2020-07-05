
#include <netdb.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <sys/socket.h> 
#include<unistd.h>
#include <dirent.h>
#define MAX 80 
#define PORT 8080 
#define SA struct sockaddr 


///function to list all the files on the server
void list(int sockfd)
{
	DIR *d;

	struct dirent *dir;

	d = opendir("/home/ubuntu/td");

	if (d)
	{
		while ((dir = readdir(d)) != NULL)
		{
			printf("%s\n", dir->d_name);
		}

		closedir(d);

	}
}

//function to receive file
void recvFile(int sockfd) 
{ 
	char buff[MAX];  // to store message from client
	char y[50];
 
	FILE *fp;
	printf("name your received file: ");
	scanf("%s",&y);
	fp=fopen(&y,"w"); // stores the file content in recieved.txt in the program directory
 
	if( fp == NULL ){
	printf("Error IN Opening File ");
	return ;
	}
 
	while( read(sockfd,buff,MAX) > 0 )
	fprintf(fp,"%s",buff);
 
	printf("File received successfully !! \n");
	printf("New File created is %s !! \n", &y);
}
void func(int sockfd) 
{ 
	char buff[MAX]; 
	int n; 
	for (;;) 
	{ 
		bzero(buff, sizeof(buff)); 
		printf("Enter the string : "); 
		n = 0; 
		while ((buff[n++] = getchar()) != '\n'); 
		write(sockfd, buff, sizeof(buff)); 
		bzero(buff, sizeof(buff)); 
		read(sockfd, buff, sizeof(buff)); 
		printf("From Server : %s", buff); 
		if ((strncmp(buff, "exit", 4)) == 0) 
		{ 
			printf("Client Exit...\n"); 
			break; 
		} 
		//for file transfer purposes
		if (strncmp("send", buff,4) == 0){
			printf("receiving file...\n");
			recvFile(sockfd);
			break;
		}

		//to receive list
		if (strncmp("list", buff,4) == 0){
			printf("receiving list...\n");
			list(sockfd);
			break;
		}

	} 
} 

  
int main() 
{ 
	int sockfd, connfd; 
	struct sockaddr_in servaddr, cli; 
	char buff[MAX];
	
	// socket create and varification 
	sockfd = socket(AF_INET, SOCK_STREAM, 0); 
	if (sockfd == -1) 
	{ 
		printf("socket creation failed...\n"); 
		exit(0); 
	} 
	else
	{
		printf("Socket successfully created..\n"); 
		bzero(&servaddr, sizeof(servaddr));
	} 
  
	// assign IP, PORT 
	servaddr.sin_family = AF_INET; 
	servaddr.sin_addr.s_addr = inet_addr("127.0.0.1"); 
	servaddr.sin_port = htons(PORT); 
  
	// connect the client socket to server socket 
	if (connect(sockfd, (SA*)&servaddr, sizeof(servaddr)) != 0) 
	{ 
		printf("connection with the server failed...\n"); 
		exit(0); 
	} 
	else
	{
		printf("connected to the server..\n"); 
	}

	// function for chat 
	func(sockfd); 

	// close the socket 
	close(sockfd); 
}

