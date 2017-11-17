import socket
import os
import time
import threading

def recv (name,sock):
    try:
        while 1:
            d=sock.recvfrom(1024)
            data=d[0]
            print data.strip()
    except:
        pass

host=''
port=9090
server=('',9090)

s=socket.socket(socket.AF_INET,socket.SOCK_DGRAM)

for i in range (5):
    threading.Thread(target=recv,args=("Recvthread",s)).start()

alias=raw_input("Name :-")
message=raw_input(alias + " :-")
while 1:
    if message != "":
        s.sendto(alias + " :-" +message,server)
        message=raw_input(alias + " :-")
s.close()
