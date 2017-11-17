//headers
#include<stdio.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<string.h>
#include<fcntl.h>


int main()
{
	//Declaring variables
	struct sockaddr_in server, client;
	int fp, n, clientsock;
	char filename[10], downloaded[10], filedata[100];
	
	//Defining socket address object
	server.sin_family = AF_INET;
	server.sin_port = 2000;
	server.sin_addr.s_addr = inet_addr("192.168.1.6");
	
	//Defining socket object
	clientsock = socket(AF_INET, SOCK_DGRAM, 0);
	n = sizeof(server);
	
	//Getting input from user
	printf("Enter filename you want to download: ");
	scanf("%s", &filename);
	
	printf("\nSave as: ");
	scanf("%s", &downloaded);
	
	sendto(clientsock, filename, sizeof(filename), 0, (struct sockaddr *)&server, n);
	
	printf("\nDownloading......");
	
	fp = open(downloaded,O_WRONLY | O_CREAT | O_TRUNC);
	
	if(fp == -1)
		printf("Error in creating file");
	
	while(1)
	{
		recvfrom(clientsock, filedata, sizeof(filedata), 0, (struct sockaddr *)&server, &n);
		if(strcmp(filedata,"end") == 0)
			break;
		printf("%s",filedata);
		write(fp, filedata, strlen(filedata));
		bzero(filedata, 100);
	}
	printf("File Downloaded Successfully");
	return 0; 
}
