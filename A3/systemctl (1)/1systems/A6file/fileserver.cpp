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
	int serversock,newserversock;
	unsigned int opt=1;
	
	serversock = socket(AF_INET, SOCK_STREAM, 0);
	setsockopt(serversock, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) ;
	
	server.sin_family = AF_INET;
	server.sin_port = 2000;
	server.sin_addr.s_addr = inet_addr("192.168.1.7");
	
	bind(serversock, (struct sockaddr *)&server, sizeof(server));
	listen(serversock,3);
	
	unsigned int n = sizeof(server);
	newserversock = accept(serversock, (struct sockaddr *)&server, &n);
	
	FILE * fp;
	fp= fopen("new.txt", "w");
	
	char buffer[1000]= {'\0'};
	
	read(newserversock, buffer, sizeof(buffer));
	fprintf(fp, "%s", buffer);
	cout<<buffer;

}

