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
	server.sin_addr.s_addr = inet_addr("192.168.1.13");
	
	clientsock = socket(AF_INET, SOCK_STREAM, 0);
	
	connect(clientsock,(struct sockaddr *)&server,sizeof(server));
	
	while(1)
	{
		cout<<"Your message: ";
		cin.getline(msg,1024);
		
		send(clientsock,msg,strlen(msg),0);
		
		read(clientsock,buffer,sizeof(buffer));
		
		cout<<"Server says: "<<buffer;
		
		bzero(buffer,1024);
		bzero(msg,1024);
		
	}
	return 0;
	
}
	
	

