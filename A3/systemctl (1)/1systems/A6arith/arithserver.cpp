#include<iostream>
#include<stdio.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<unistd.h>
#include<strings.h>
#include<arpa/inet.h>

using namespace std;

double arithCal(int choice, int opr1, int opr2);

int main()
{
	struct sockaddr_in server;
	
	int serversock,newserversock;
	int opt=1;
	serversock = socket(AF_INET, SOCK_STREAM, 0);
	setsockopt(serversock, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
	
	server.sin_family = AF_INET;
	server.sin_port = 2000;
	server.sin_addr.s_addr =inet_addr("192.168.1.7");
	
	bind(serversock, (struct sockaddr *)&server, sizeof(server));
	listen(serversock, 1);
	
	unsigned int n = sizeof(server);	
	newserversock = accept(serversock, (struct sockaddr *)&server, &n);
	char ch[20]={'\0'},op1[20]={'\0'},op2[20]={'\0'},result[200]={'\0'};
	int choice,opr1,opr2;
	double res;
	while(1)
	{
		read(newserversock,ch, 20);
		choice = atoi(ch);
		cout<<choice<<endl;
		read(newserversock,op1,20);
		//cout<<op1<<endl;
		read(newserversock,op2, 20);
		//cout<<op2<<endl;
		
		//cout<<choice;
		opr1 = atoi(op1);
		opr2 =atoi(op2);
		
		res = arithCal(choice, opr1, opr2);
		
		sprintf(result, "%lf", res);
		cout<<"\nResult is :"<<result<<endl;
		send(newserversock, result, sizeof(result), 0);
		


	}

	return 0;

}


double arithCal(int choice, int opr1, int opr2)
{
	if(choice ==1)
		return opr1+opr2;
	else if(choice == 2)
		return opr1-opr2;
	else if(choice == 3)
		return opr1*opr2;
	else if(choice == 4)
		return opr1/opr2;
	else
		return 0;


}





