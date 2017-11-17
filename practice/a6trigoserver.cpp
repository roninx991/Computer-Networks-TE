#include<iostream>
#include<string.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<math.h>

using namespace std;

double trigo(int ch, double a);
int main()
{
	struct sockaddr_in server,client;
	int serversock,clientsock;
	char opt[100]={'\0'},angle[100]={'\0'},buffer[100]={'\0'};
	double a,r;
	int ch;
	
	server.sin_family = AF_INET;
	server.sin_port = 2000;
	server.sin_addr.s_addr = INADDR_ANY;
	
	serversock = socket(AF_INET, SOCK_STREAM, 0);
	
	bind(serversock,(struct sockaddr *)&server, sizeof(server));
	
	listen(serversock,3);
	
	unsigned int n = sizeof(client);
	
	clientsock = accept(serversock,(struct sockaddr *)&client, &n);
	ch = 0;
	
	while(ch!=7)
	{
		read(clientsock,opt,100);
		ch = atoi(opt);
		cout<<"Your choice is: "<<ch<<endl;
	
		read(clientsock,angle,100);
		cout<<"Your angle is: "<<angle;
		a = atoi(angle);
		a = (a * M_PI)/180;
		r = trigo(ch,a);
		
		sprintf(buffer,"%lf",r);
		send(clientsock,buffer,strlen(buffer),0);
	
		bzero(angle,100);
		bzero(opt,100);
	}
	return 0;
}

double trigo(int ch, double a)
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
