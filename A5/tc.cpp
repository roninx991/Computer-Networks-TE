#include<iostream>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<string.h>

using namespace std;

int main()
{
	struct sockaddr_in server;
	int clientsock;
	FILE *fp;
	char buffer[1024]={'\0'},str[1024]={'\0'};
	
	clientsock = socket(AF_INET, SOCK_DGRAM, 0);
	
	server.sin_family = AF_INET;
	server.sin_port = 2000;
	server.sin_addr.s_addr = inet_addr("192.168.1.13");
	
	fp = fopen("old.txt","r");
	
	while(fgets(buffer, sizeof(buffer), fp))
	{
		strcat(str,buffer);
	}
	cout<<str;
	sendto(clientsock, str, strlen(str), 0, (struct sockaddr *)&server, sizeof(server));
	
	cout<<"Sent successfully";
}
