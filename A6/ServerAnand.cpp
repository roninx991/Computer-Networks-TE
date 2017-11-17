#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <iostream>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>
#define PORT 8000
#define atoa(x) #x

using namespace std;

double returnTrigonometric(int c, double x);
int main(int argc, char const *argv[]) {

    struct sockaddr_in address;
    int server_fd, new_socket, valread, val, opt = 1, addrlen = sizeof(address);
    char temp[1024] = {0}, buffer[1024] = {0}, buffer1[10240] = {0};
    int val1, c;
    double r, x;
    char y;
	char buffer2[100] = {0}, buffer3[100] = {0}, buffer4[100] = {0}, a[100] = {0};	
      
    // Creating socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }
    // Forcefully attaching socket to the port 8000
    if (setsockopt(server_fd, SOL_SOCKET,SO_REUSEADDR, &opt, sizeof(opt)) == -1) {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }
    
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons( PORT );
      
    // Forcefully attaching socket to the port 8000
    if (bind(server_fd, (struct sockaddr *)&address, addrlen) == -1) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
    
    if (listen(server_fd, 3) == -1) {
        perror("listen");
        exit(EXIT_FAILURE);
    }
    if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) == -1) {
        perror("accept");
        exit(EXIT_FAILURE);
    }

	valread = read(new_socket, temp, 1024);
	while(atoi(temp) != 4) {
		printf("Choice selected by the user : %d\n", atoi(temp));
		switch(atoi(temp)) {
			case 1:
				printf("Note : The user will chat with you until the message ends with 'end'\n");
				valread = read(new_socket, buffer, 1024);
				printf("Client : %s\n", buffer);
				while(1) {
					char yo[1024] = {'\0'}, buff[1024] = {'\0'};
					printf("Enter the Response Message : ");
					cin.getline(yo, 1024);
					cin.ignore(0);
					send(new_socket, yo, strlen(yo), 0);
					valread = read(new_socket, buff, 1024);
					printf("Client: %s\n", buff);
					if (strcmp(buff, "end") == 0) {
						cout << "User has ended this session\n";
						break;
					}
				}
				break;
			case 2:	
				val = read(new_socket, buffer1, 1024);
				printf("%s\n", buffer1 );
				FILE *fp;
				fp = fopen("new.txt", "w");
				fprintf(fp, "%s", buffer1);
				break;
			case 3:
				val1 = read(new_socket, buffer2, 1024);
				c = atoi(buffer2);
				val1 = read(new_socket,buffer3,1024);
				x = atoi(buffer3)*M_PI/180;
				printf("x = %lf\n", x);
				r = returnTrigonometric(c, x);
				printf("Result is: %lf\n", r);
				sprintf(a, "%lf", r);
				send(new_socket, a, strlen(a), 0);
				break;				
			case 4:
				val = read(new_socket, temp, 1024);
				printf("Client is disconnected... Exiting...\n");
				break;
			default:
				printf("INVALID OPTION SELECTED BY USER..\n");
				exit(0);
				break;
		}
		valread = read(new_socket, temp, 1024);
	}   
    return 0;
}


double returnTrigonometric(int c, double x) {
        return (c == 1 ? sin(x) : (c == 2 ? cos(x) : (c == 3 ? tan(x) : (c == 4 ? 1/tan(x) : (c == 5 ? 1/cos(x) : 1/sin(x))))));
}

