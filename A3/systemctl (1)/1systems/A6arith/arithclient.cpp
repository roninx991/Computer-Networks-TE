#include<iostream>
#include<stdio.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<unistd.h>
#include<strings.h>
#include<arpa/inet.h>

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
	char ch[20]={'\0'},op1[20]={'\0'},op2[20]={'\0'};
	char result[200];
	
	while(1)
	{
		cout<<"enter choice :\n 1.add \n2.sub \n3.mul \n4div\n";
		cin>>ch;
		send(clientsock, ch,20, 0);
		cout<<"Enter 1st operand :";
		cin>>op1;
		send(clientsock, op1, 20, 0);
		cout<<"\nEnter 2nd opearnd :";
		cin>>op2;
		send(clientsock, op2, 20, 0);
		
		read(clientsock, result, sizeof(result));
		cout<<"\nResult is :"<<result;
		
	}

	return 0;


}
