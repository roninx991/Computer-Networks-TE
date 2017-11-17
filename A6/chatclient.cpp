#include<stdio.h>
#include<iostream>
#include<sys/types.h>
#include<sys/socket.h>
#include<strings.h>
#include<arpa/inet.h>
#include <sys/uio.h>
#include <unistd.h>

using namespace std;

int main()
{
	struct sockaddr_in server;
	int clientsock;
	int opt=1;
	
	clientsock = socket(AF_INET, SOCK_STREAM, 0);
	
	server.sin_family = AF_INET;
	server.sin_port = 2000;
	server.sin_addr.s_addr= inet_addr("192.168.1.5");
	
	connect(clientsock, (struct sockaddr *)&server, sizeof(server));

	cout<<"type 'end' to end this conversation\n";
	
	while(1)
	{
		char msg[1024]={'\0'},buffer[1024]={'\0'};
		cout<<"enter the message to send"<<endl;
		
		cin.getline(msg,1024);
		cin.ignore(0);
		
		send(clientsock, msg, strlen(msg), 0);
		
		if(strcmp(msg,"end")==0)
			exit(0);
		
		read(clientsock, buffer, 1024);
		cout<<"\nServer says: "<<buffer<<endl;
	
	
	
	}
	
	
	
	
	
	

	return 0;

}



































