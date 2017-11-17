#include<iostream>
#include<string.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>

using namespace std;

int main()
{
	struct sockaddr_in server,client;
	int serversock,clientsock;
	char buffer[1024]={'\0'},msg[1024]={'\0'};
	FILE *fp;
	
	server.sin_family = AF_INET;
	server.sin_port = 2000;
	server.sin_addr.s_addr = INADDR_ANY;
	
	serversock = socket(AF_INET, SOCK_STREAM, 0);
	
	bind(serversock,(struct sockaddr *)&server, sizeof(server));
	
	listen(serversock,3);
	
	unsigned int n = sizeof(client);
	
	clientsock = accept(serversock,(struct sockaddr *)&client, &n);
	
	fp = fopen("new.txt","w");

	read(clientsock,buffer,sizeof(buffer));
	
	fprintf(fp,"%s",buffer);
	
	cout<<buffer;
	return 0;
}
