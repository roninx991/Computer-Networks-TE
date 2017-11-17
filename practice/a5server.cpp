#include<iostream>
#include<string.h>
#include<sys/socket.h>
#include<arpa/inet.h>

using namespace std;

int main()
{
	struct sockaddr_in server,client;
	int serversock,clientsock;
	char buffer[1024],msg[1024];
	
	server.sin_family = AF_INET;
	server.sin_port = 2000;
	server.sin_addr.s_addr = INADDR_ANY;
	
	serversock = socket(AF_INET, SOCK_DGRAM, 0);
	
	bind(serversock,(struct sockaddr *)&server, sizeof(server));
	
	cout<<"Server started"<<endl;
	
	unsigned int n = sizeof(client);
	
	while(1)
	{
		recvfrom(serversock,buffer,sizeof(buffer),0,(struct sockaddr *)&client, &n);
		
		cout<<"Client says: "<<buffer;
		
		cout<<"Your reply: ";
		
		cin.getline(msg,1024);
		
		sendto(serversock,msg,strlen(msg),0,(struct sockaddr *)&client, sizeof(client));
		bzero(buffer,1024);
		bzero(msg,1024);
	}
	
	return 0;
	
}
