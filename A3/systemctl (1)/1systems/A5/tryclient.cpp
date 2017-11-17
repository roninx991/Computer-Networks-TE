#include<stdio.h>
#include<iostream>
#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<strings.h>

using namespace std;

int main()
{
	struct sockaddr_in server;
	int clientsock = socket(AF_INET, SOCK_DGRAM, 0);
	
	server.sin_family = AF_INET;
	server.sin_port = 2000;
	server.sin_addr.s_addr = inet_addr("192.168.1.7");
	
	FILE * fp;
	fp = fopen("old.txt", "r");
	
	char buffer[1048]={'\0'};
	char str[1048] = {'\0'};
	
	while(fgets(buffer, sizeof(buffer), fp))
		strcat(str, buffer);
	cout<<str;
	sendto(clientsock, str, sizeof(buffer), 0, (struct sockaddr *)&server, sizeof(server));
	

}
