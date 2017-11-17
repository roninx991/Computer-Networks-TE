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
	int serversock,newserversock;
	int opt=1;
	
	serversock = socket(AF_INET, SOCK_STREAM, 0);
	setsockopt(serversock, SOL_SOCKET,SO_REUSEADDR, &opt, sizeof(opt));
	
	server.sin_family = AF_INET;
	server.sin_port = 2000;
	server.sin_addr.s_addr= inet_addr("192.168.1.5");
	
	bind(serversock, (struct sockaddr *)&server, sizeof(server));
	listen(serversock, 3);
	unsigned int n=sizeof(server);
	newserversock = accept(serversock, (struct sockaddr *)&server, &n);
	
	char buff[1024]={'\0'};
	
	
	//read(newserversock, buff, 1024);
	//cout<<"Client says: "<<buff<<endl;
	
	while(1)
	{
		char msg[1024]={'\0'},buffer[1024]={'\0'};
		read(newserversock, buffer, 1024);
		
		if(strcmp(buffer,"end")==0)
		{
			cout<<"user has ended the conversation"<<endl;
			exit(0);
		}

		cout<<"client says: "<<buffer<<endl;

		cout<<"enter the response msg\n";
		cin.getline(msg,1024);
		cin.ignore(0);
		
		send(newserversock, msg, strlen(msg),0);
		
		
		
		
	
	
	}
	
	



}










































