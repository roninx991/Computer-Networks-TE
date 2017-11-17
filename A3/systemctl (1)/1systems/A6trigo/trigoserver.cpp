#include<iostream>
#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<strings.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<math.h>

using namespace std;
double trigoFun(int c, double r);
int main()
{
	struct sockaddr_in server;
	int opt=1;
	int serversock, newserversock;
	
	serversock = socket(AF_INET, SOCK_STREAM, 0);
	setsockopt(serversock, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
	
	server.sin_family = AF_INET;
	server.sin_port = 2000;
	server.sin_addr.s_addr = inet_addr("192.168.1.5");
	
	bind(serversock, (struct sockaddr *)&server, sizeof(server));
	listen(serversock, 3);
	
	unsigned int n = sizeof(server);
	newserversock = accept(serversock, (struct sockaddr *)&server, &n); 
	
	char op[100]={0};
	int ch;
	char angle[100]={0};
	double a,r;
	char str[100]={0};
	
	while(ch!=7)
	{
		read(newserversock, op, 1024);
		ch= atoi(op);
		
		read(newserversock, angle, 1024);
		a= atoi(angle)*M_PI/180;
		
		r = trigoFun(ch,a);
		cout<<"result is : "<<r<<endl;
		sprintf(str, "%lf", r);
		send(newserversock, str, strlen(str), 0);
	}
		
		
		
	 	
	
	
	return 0;
	
	
}

double trigoFun(int c, double a)
{
	if(c==1)
		return sin(a);
	else if(c==2)
		return cos(a);
	else if(c==3)
		return tan(a);
	else if(c==4)
		return 1/sin(a);
	else if(c==5)
		return 1/cos(a);
	else if(c==6)
		return 1/tan(a);



}
















