#include <stdio.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include<unistd.h>
#include <dirent.h>
#define MAX 80
#define PORT 8080
#define SA struct sockaddr

//function to list all the files on the server
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

//function to send file
void sentfile(int sockfd)
{
	char buff[MAX];       // for read operation from file and used to sent operation 
 
	// create file 
	FILE *fp;
	char x;
	printf("which file to send: ");
	scanf("%s", &x);
	fp=fopen(&x,"r");  // open file uses both stdio and stdin header files
	
	// file should be present at the program directory
	if( fp == NULL ){
	printf("Error IN Opening File .. \n");
	return ;
	}
 
	while ( fgets(buff,MAX,fp) != NULL ) // fgets reads upto MAX character or EOF 
	write(sockfd,buff,sizeof(buff));  // sent the file data to stream
 
	fclose (fp);       // close the file 
 
	printf("File Sent successfully !!! \n");
 
}
//chat between client and server.
void func(int sockfd)
{
	char buff[MAX];
	int n;
	//infinite loop for chat
	for(;;) {
		bzero(buff, MAX);

		//read the message from client and copy it in buffer
		read(sockfd, buff, sizeof(buff));

		//read buffer which contains the client contents
		printf("From client: %s\t To Client :  ", buff);
		bzero(buff, MAX);
		n = 0;

		//copy server message in the buffer
		while ((buff[n++] = getchar()) != '\n');

		//and send that buffer to client
		write(sockfd, buff, sizeof(buff));

		//if msg contains "Exit" then server exit and chat ended.
		if (strncmp("exit", buff, 4) == 0){
			printf("Server Exit...\n");
			break;
		}
	
		//for file transfer purposes
		if (strncmp("send", buff, 4) == 0){
			printf("sending file....\n");
			sentfile(sockfd);
			break;
		}
		
		if (strncmp("list", buff, 4) == 0){
			break;
		}
	}
}

//Driver function
int main()
{
	int sockfd, connfd, len;
	struct sockaddr_in servaddr, cli;
	char buff[MAX];

	//socket create and verification
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd == -1) {
		printf("socket creation failed...\n");
		exit(0);
	}
	else
		printf("socket successfully created..\n");
	bzero(&servaddr, sizeof(servaddr));

	//assign IP, PORT
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(PORT);

	//Binding newly created socket to given IP and verification
	if ((bind(sockfd, (SA*)&servaddr, sizeof(servaddr))) != 0) {
		printf("socket bind failed...\n");
		exit(0);
	}
	else
		printf("socket successfuly binded..\n");

	//Now server is ready to listen and verification
	if ((listen(sockfd, 5)) != 0) {
		printf("Listen failed...\n");
		exit(0);
	}
	else
		printf("server listening..\n");
	len = sizeof(cli);

	//accept the data packet from client and verification
	connfd = accept(sockfd, (SA*)&cli, &len);
	if (connfd < 0 ) {
		printf("server accept failed...\n");
		exit(0);
	}
	else
		printf("server accept the client...\n");

	//function for chatting between client and server
	func(connfd);

	//after chatting close the socket
	close(sockfd);
}

