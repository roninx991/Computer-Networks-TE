#include<stdio.h>
#include<iostream>
#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<strings.h>
#include<unistd.h>

using namespace std;

int main()
{
	struct sockaddr_in server;
	int clientsock;
	
	clientsock = socket(AF_INET, SOCK_STREAM, 0);
	
	server.sin_family = AF_INET;
	server.sin_port = 2000;
	server.sin_addr.s_addr = inet_addr("192.168.1.5");
	
	connect(clientsock, (struct sockaddr *)&server, sizeof(server));
	
	char op[10]={'\0'};
	char angl[10]={'\0'};
	char buffer[10]={'\0'};
	int ch;
	while(ch!=7)
	{
		cout<<"1.sin \t 2.cos \t 3.tan \t 4.cosec \t 5.sec \t 6.cot"<<endl;
		cout<<"enter choice: ";
		gets(op);
		ch=atoi(op);
		send(clientsock, op, strlen(op), 0);
		cout<<"enter angle in degree"<<endl;
		gets(angl);
		send(clientsock, angl, strlen(angl), 0);
		
		read(clientsock,buffer,1024);
		cout<<"the result is :"<<buffer<<endl; 
		
	}
		


	return 0;
}

























