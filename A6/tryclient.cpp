#include<iostream>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<string.h>
#include<math.h>

using namespace std;

int main()
{
	struct sockaddr_in server,client;
	int serversock,clientsock;
	char op[100]={'\0'},angle[100]={'\0'},buffer[1024]={'\0'};
	int ch;
	double a;
	
	server.sin_family = AF_INET;
	server.sin_port = 2000;
	server.sin_addr.s_addr = inet_addr("192.168.1.13");
	
	clientsock = socket(AF_INET, SOCK_STREAM, 0);
	
	connect(clientsock, (struct sockaddr *)&server, sizeof(server));
	
	while(ch != 7)
	{
		cout<<"Select option:\n1.Sine\n2.Cosine\n3.Tangent\n4.Cosecant\n5.Secant\n6.Cotangent\n7.Exit\n\n";
		cin>>op;
		send(clientsock,op,100,0);
		ch = atoi(op);
		cout<<"Enter angle: ";
		cin>>angle;
		send(clientsock,angle,100,0);
		
		read(clientsock,buffer,1024);
		cout<<"Result is: "<<buffer;
		
	}
	
	return 0;
}
		
