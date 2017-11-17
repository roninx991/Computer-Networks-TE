//headers
#include<stdio.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<fcntl.h>
#include<string.h>

int main()
{
	//Declaration of variables
	struct sockaddr_in server, client;
	int serversock;
	int fp, end,n;
	char filename[20], buffer[100];
	
	//Definition of server socket address object	
	server.sin_family = AF_INET;
	server.sin_port = 2000;
	server.sin_addr.s_addr = INADDR_ANY;
	
	//Definition of server socket object
	serversock = socket(AF_INET, SOCK_DGRAM, 0);
	
	//binding of server socket object
	bind(serversock, (struct sockaddr *)&server, sizeof(server));
	
	//receiving data from client
	n = sizeof(client);
	recvfrom(serversock, filename, sizeof(filename), 0, (struct sockaddr *)&client, &n);
	
	//file opening
	fp = open(filename, O_RDONLY);
	
	//file reading and sending data...
	while(1)
	{
		end = read(fp, buffer, sizeof(buffer));

		if(end == 0)
			break;
		sendto(serversock, buffer, sizeof(buffer), 0, (struct sockaddr *)&client, n);
		
		bzero(buffer, 100);
	}
	//ending reading of file and transfer operation
	strcpy(buffer, "end");
	sendto(serversock, buffer, sizeof(buffer), 0, (struct sockaddr *)&client, n);
	return 0;
}
