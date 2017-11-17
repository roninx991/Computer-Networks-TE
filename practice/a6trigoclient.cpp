#include<iostream>
#include<string.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<math.h>
using namespace std;

int main()
{
	struct sockaddr_in server,client;
	int serversock,clientsock;
	char opt[100]={'\0'},angle[100]={'\0'},buffer[100]={'\0'};
	int ch;
	double a;
		
	server.sin_family = AF_INET;
	server.sin_port = 2000;
	server.sin_addr.s_addr = inet_addr("192.168.1.13");
	
	clientsock = socket(AF_INET, SOCK_STREAM, 0);
	
	connect(clientsock,(struct sockaddr *)&server,sizeof(server));
	ch = 0;
	while(ch != 7)
	{
		cout<<"Choose option:\n1.Sin\n2.Cos\n3.Tan\n4.Cosec\n5.Sec\n6.Cot\n7.Exit\n\n";
		cin>>opt;
		send(clientsock,opt,100,0);
		ch = atoi(opt);
		cout<<"Enter angle: ";
		cin>>angle;
		send(clientsock,angle,100,0);
		read(clientsock,buffer,100);
		cout<<"Your answer is: "<<buffer;
		bzero(angle,100);
		bzero(opt,100);
	}
	
	return 0;
	
}
	
	

