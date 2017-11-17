#include<iostream>
#include<stdio.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<strings.h>
#include<arpa/inet.h>
#include<unistd.h>

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

	char buffer[1024],msg[1024];
	
	while(1)
	{
	
	cout<<"\n send messages :";
	cin>>msg;
	send(clientsock, msg, sizeof(msg), 0);

	read(clientsock, buffer, sizeof(buffer));
	cout<<"\nServer says : "<<buffer<<endl;
	
	
	}


}
