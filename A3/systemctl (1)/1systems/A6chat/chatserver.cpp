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
	int serversock,newserversock;
	int opt=1;
	
	serversock= socket(AF_INET, SOCK_STREAM, 0);
	setsockopt(serversock, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
	
	server.sin_family = AF_INET;
	server.sin_port = 2000;
	server.sin_addr.s_addr = inet_addr("192.168.1.7");
	
	bind(serversock, (struct sockaddr *)&server, sizeof(server));
	listen(serversock,1);
	
	unsigned int n= sizeof(server);
	newserversock = accept(serversock, (struct sockaddr *)&server, &n);
	
	char buffer[1024],msg[1024];

	while(1)
	{
	read(newserversock, buffer, sizeof(buffer));
	cout<<"\nClient says : "<<buffer<<endl;
	cout<<"\nEnter msg :";
	cin.getline(msg, sizeof(msg));
	send(newserversock, msg, sizeof(msg), 0);
	
	}
	




}
