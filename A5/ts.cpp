#include<iostream>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<string.h>

using namespace std;

int main()
{
	struct sockaddr_in server,client;
	int serversock;
	FILE *fp;
	char buffer[1024]={'\0'};
	
	serversock = socket(AF_INET, SOCK_DGRAM, 0);
	
	server.sin_family = AF_INET;
	server.sin_port = 2000;
	server.sin_addr.s_addr = INADDR_ANY;
	
	bind(serversock, (struct sockaddr *)&server, sizeof(server));
	
	fp = fopen("new.txt","w");
	
	unsigned int n = sizeof(client); 
	
	recvfrom(serversock, buffer, sizeof(buffer), 0, (struct sockaddr *)&client, &n);
	cout<<buffer;
	fprintf(fp, "%s", buffer);
	
	cout<<"File received successfully\n";
	
	return 0;
	
}
