#include<iostream>
#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<strings.h>

using namespace std;

int main()
{
	struct sockaddr_in server;
	int clientsock;
	
	clientsock = socket(AF_INET, SOCK_STREAM, 0);
	
	server.sin_family = AF_INET;
	server.sin_port = 2000;
	server.sin_addr.s_addr = inet_addr("192.168.1.7");
	
	connect(clientsock, (struct sockaddr *)&server, sizeof(server));

	FILE * fp;
	fp = fopen("old.txt", "r");
	
	char buffer[1000]={'\0'};
	char str[1000]={'\0'};
	
	while(fgets(buffer, sizeof(buffer), fp))
		strcat(str, buffer);
	cout<<str;
	send(clientsock, str, sizeof(str), 0);

	return 0;
}
