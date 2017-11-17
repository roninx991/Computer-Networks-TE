#include<iostream>
#include<string.h>
#include<sys/socket.h>
#include<arpa/inet.h>

using namespace std;

int main()
{
	struct sockaddr_in server,client;
	int serversock,clientsock;
	char buffer[1024] = {'\0'},msg[1024]={'\0'};
	
	server.sin_family = AF_INET;
	server.sin_port = 2000;
	server.sin_addr.s_addr = INADDR_ANY;
	
	clientsock = socket(AF_INET, SOCK_DGRAM, 0);
	
	unsigned int n = sizeof(server);
	
	while(1)
	{
		cout<<"Enter your message: "<<endl;
		cin.getline(msg,1024);
		
		sendto(clientsock,msg,strlen(msg),0,(struct sockaddr *)&server,sizeof(server));
		
		recvfrom(clientsock,buffer,sizeof(buffer),0,(struct sockaddr *)&server,&n);
		
		cout<<"Server says: "<<buffer<<endl;
		bzero(msg,1024);
		bzero(buffer,1024);
	}
	
	return 0;
	
}
