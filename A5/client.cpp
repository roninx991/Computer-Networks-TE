#include<stdio.h>
#include<iostream>
#include<sys/socket.h>
#include<sys/types.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>

using namespace std;

int main()
{
	struct sockaddr_in server;
	int clientsock;
	
	clientsock = socket(AF_INET, SOCK_DGRAM, 0);
	
	server.sin_family =AF_INET;
	server.sin_port=2000;
	server.sin_addr.s_addr = inet_addr("192.168.1.7");
	

	//connect(clientsock, (struct sockaddr *)&server, sizeof(server));
	
	FILE *fp;
	char buffer[1024]={'\0'},str[1024]={'\0'};
	fp = fopen("old.txt", "r");
	
	
	while(fgets(buffer, sizeof(buffer), fp))
	{
		strcat(str,buffer);
	}
	cout<<str;
	str[strlen(str)-1]='\0';
	sendto(clientsock, str, strlen(str),0,(struct sockaddr *)&server, sizeof(server));
	
	cout<<"\nFile sent succesfully"<<endl;

	return 0;
}


























