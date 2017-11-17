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
	
	server.sin_family = AF_INET;
	server.sin_port = 2000;
	server.sin_addr.s_addr = INADDR_ANY;
	
	serversock = socket(AF_INET, SOCK_STREAM, 0);
	
	bind(serversock,(struct sockaddr *)&server, sizeof(server));
	
	listen(serversock,3);
	
	unsigned int n = sizeof(client);
	
	clientsock = accept(serversock,(struct sockaddr *)&client, &n);
	
	while(1)
	{
		read(clientsock,buffer,sizeof(buffer));
		
		cout<<"Client says: "<<buffer;
		
		cout<<"Your reply: ";
		
		cin.getline(msg,1024);
		
		send(clientsock,msg,strlen(msg),0);
		
		bzero(buffer,1024);
		bzero(msg,1024);
	}
	return 0;
}
