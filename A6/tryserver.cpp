#include<iostream>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<string.h>
#include<math.h>

using namespace std;

double trigo(int ch,double a);

int main()
{
	struct sockaddr_in server,client;
	int serversock,clientsock;
	char op[100]={'\0'},angle[100]={'\0'},str[100]={'\0'};
	double a,r;
	int ch;
	
	serversock = socket(AF_INET, SOCK_STREAM, 0);
	
	server.sin_family = AF_INET;
	server.sin_port = 2000;
	server.sin_addr.s_addr = INADDR_ANY;
	
	bind(serversock, (struct sockaddr *)&server, sizeof(server));
	
	listen(serversock, 3);
	
	unsigned int n = sizeof(client);
	
	clientsock = accept(serversock,(struct sockaddr *)&client, &n);
	
	
	while(ch != 7)
	{
		read(clientsock,op,100);
		ch = atoi(op);
		cout<<"Client has selected choice number: "<<ch<<endl;
		read(clientsock,angle,100);
		a = atoi(angle);
		a = (a * M_PI)/180;
		r = trigo(ch,a);
		
		cout<<"Answer is: "<<r<<endl;
		
		sprintf(str,"%lf",r);
		
		send(clientsock,str,strlen(str),0);
	}
	return 0;
}

double trigo(int ch,double a)
{
	if(ch == 1)
		return sin(a);
	else if(ch == 2)
		return cos(a);
	else if(ch == 3)
		return tan(a);
	else if(ch == 4)
		return 1/sin(a);
	else if(ch == 5)
		return 1/cos(a);
	else if(ch == 6)
		return 1/tan(a);
	else
		return 0;
}
	
