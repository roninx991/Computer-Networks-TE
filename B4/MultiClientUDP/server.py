import os
import time
import socket

host=''
port=9090

s=socket.socket(socket.AF_INET,socket.SOCK_DGRAM)
s.bind((host,port))

clients =[]

print "socket binded"

print ("socket binded to port %s" %(port))

while 1:
    try:
        d=s.recvfrom(1024)
        data=d[0]
        addr=d[1]
        if addr not in clients:
            clients.append(addr)
        
        for client in clients:
            if addr!=client:
                s.sendto(data,client)
                
        print str(addr) + ": :" +str(data)       
    except:
        pass
        
s.close()
