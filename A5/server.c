#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<fcntl.h>
#include<string.h>
#define BUFFLEN 100
#define PORTNO 2000
main()
{
    struct sockaddr_in server,client;
    int serversock,n,fp,end;
    char filename[20],buffer[BUFFLEN];
    serversock=socket(AF_INET,SOCK_DGRAM,0);        //int domain, int type, int protocol)   return socket file descriptor
    server.sin_family=AF_INET;                      //addresses from the internet, IP addresses specifically
    server.sin_port=PORTNO;                         
    server.sin_addr.s_addr=inet_addr("192.168.1.6");      //address of client for same machine local host

    bind(serversock,(struct sockaddr *)&server,sizeof(server));    //sockfd, struct sockaddr *my_addr, int addrlen
    n=sizeof(client);

    recvfrom(serversock,filename,sizeof(filename), 0,(struct sockaddr *)&client,&n);  /*int sockfd, void *buf, int len, unsigned int flags,
             struct sockaddr *from, int *fromlen*/
    fp=open(filename,O_RDONLY);                
    while(1)
    {
        end=read(fp,buffer,sizeof(buffer));             //fs=socket descriptor, void *buf=buffer name, ssize_t N=no.of bytes)
        if(end==0)
            break;
        sendto(serversock,buffer,sizeof(buffer),0,(struct sockaddr *)&client,n);   /*fd, const *buf=name, size_t len=length,
               int flags=normal data, const struct sockaddr *to=socket address,
               socklen_t tolen=no.of bytes
*/        bzero(buffer,100);
    }
    strcpy(buffer,"end");
    sendto(serversock,buffer,sizeof(buffer),0,(struct sockaddr *)&client,n);
}
