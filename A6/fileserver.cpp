#include<stdio.h>
#include<iostream>
#include<sys/socket.h>
#include<sys/types.h>
#include<strings.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<stdlib.h>


using namespace std;

int main()
{
	struct sockaddr_in server;
	int serversock,newserversock;
	int opt=1;
	
	serversock = socket(AF_INET, SOCK_STREAM, 0);
	setsockopt(serversock, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
	
	server.sin_family = AF_INET;
	server.sin_port = 2000;
	server.sin_addr.s_addr = inet_addr("192.168.1.5");
	
	bind(serversock, (struct sockaddr *)&server, sizeof(server));
	listen(serversock, 3);
	
	unsigned int n= sizeof(server);
	newserversock = accept(serversock, (struct sockaddr *)&server, &n);
	
	FILE *fp;
	char buffer[1024]={0};
	
	read(newserversock, buffer, 1024);
	cout<<buffer<<endl;
	
	fp= fopen("new.txt","w");
	fprintf(fp,"%s", buffer);
	
	cout<<"\nReceived successfully!!"<<endl;














	return 0;
}






























