#include <stdio.h>
#include <iostream>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <arpa/inet.h>			//for inet_pton()
#include <string.h>			//for memset()
#include <unistd.h>
#define PORT 8000 

using namespace std;

/*
struct sockaddr_in
{
	short sin_family;
	unsigned short sin_port;
	struct in_addr sin_addr;
	char sin_zero[8]; (used for padding)
}
struct in_addr
{
	unsigned long s_addr
}
*/


int main(int argc, char const *argv[])
{
    struct sockaddr_in address, serv_addr;			//sockaddr_in can only be used for internet connection or network communication
    int sock = 0, valread;
    char temp1[1024] = {"1"}, temp[10], buffer[1024] = {'\0'},  buffer1[1024] = {'\0'};
    char op[10] = {'\0'}, x[10] = {'\0'}, y[10] = {'\0'}, buffer3[10] = {'\0'}, str[1024] = {'\0'};
	FILE *fp; 
	
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) == -1) {		//
        printf("\n ERROR IN SOCKET CREATION \n");
        return -1;
    }
   //void *memset(void *s, int c, size_t n);
    memset(&serv_addr, '0', sizeof(serv_addr));		//The  memset()  function  fills  the  first  n  bytes of the memory area pointed to by s with the constant byte c.
  
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
      
    // Convert IPv4 and IPv6 addresses from text to binary form
    if(inet_pton(AF_INET, argv[1], &serv_addr.sin_addr)<=0)  { 	
        printf("Invalid address/ Address not supported \n");
        return -1;
    }
  
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        printf("Connection Failed \n");
        return -1;
    }
    while(atoi(temp) != 4) {
		printf("1. Send Message To Server\n2. Transfer File\n3. Trigonometric Calculator\n4. Exit\nEnter the choice : ");
		fgets(temp, 1024-1, stdin);
		temp[strcspn(temp, "\n")] = 0; 
	 	send(sock, temp, strlen(temp), 0);
		switch(atoi(temp)) {
			case 1 :
				printf("Note : If you want to end the conversation, please enter 'end' to end the session...\n");
				while(1) {
					char yo[1024] = {'\0'}, buff[1024] = {'\0'};
					printf("Enter the message to Send : ");
					cin.getline(yo, 1024);
					cin.ignore(0);
					send(sock, yo, strlen(yo), 0);
					if(strcmp(yo, "end") == 0) break;
					valread = read(sock, buff, 1024);
					printf("Server : %s\n", buff);
				}
				break;
				
			 case 2:
				fp = fopen("old.txt", "r");
				while (fgets(buffer, sizeof(buffer), fp))
					strcat(str, buffer);
				printf("%s", str);
				str[strlen(str)-1] = '\0';
				send(sock, str, strlen(str), 0);
				printf("\nFile Sent Successfully\n");
				break;
				
			 case 3:	
			printf("Enter The Function :\n1. Sine(sin)\n2. Cosine(cos)\n3. Tangent(tan)\n4. Cotangent(cot)\n5. Secant(sec)\n6. Cosecant(cosec)\n");
				fgets(op, 100-1, stdin);
				send(sock, op, strlen(op), 0);
				printf("Enter The angle in degrees : ");
				fgets(x, 100-1, stdin);
				send(sock, x, strlen(x), 0);
				valread = read(sock , buffer3, 1024);
				printf("The Result is : %s\n",buffer3);
				break;
			
			case 4:
				printf("Exiting...\n");
				break;
			
			default:
				printf("Enter the choice correctly...\n");
				break;			    
		} 
	}  
	return 0;
}
