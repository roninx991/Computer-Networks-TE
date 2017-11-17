#include<stdio.h>
#include<iostream>
#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<strings.h>

using namespace std;

int main()
{
	struct sockaddr_in server;
	int serversock = socket(AF_INET, SOCK_DGRAM, 0);
	
	server.sin_family = AF_INET;
	server.sin_port = 2000;
	server.sin_addr.s_addr = inet_addr("192.168.1.7");

	bind(serversock, (struct sockaddr *)&server, sizeof(server));
	
	FILE * fp;
	fp = fopen("new1.txt", "w");
	char buffer[1024]={'\0'};
	unsigned int n= sizeof(server);

	recvfrom(serversock, buffer, sizeof(buffer), 0, (struct sockaddr *)&server, &n);
	
	cout<<buffer;
	fprintf(fp, "%s", buffer);
	
	cout<<"\n Successfull"<<endl;
	
	



}
