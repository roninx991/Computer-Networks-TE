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
	server.sin_addr.s_addr = inet_addr("192.168.1.13");
	
	clientsock = socket(AF_INET, SOCK_STREAM, 0);
	
	connect(clientsock,(struct sockaddr *)&server,sizeof(server));
	
	fp = fopen("old.txt","r");
	
	while(fgets(buffer,1024,fp))
	{
		strcat(msg,buffer);
	}
	
	cout<<msg;
	send(clientsock,msg,strlen(msg),0);
	
	return 0;
	
}
	
	

