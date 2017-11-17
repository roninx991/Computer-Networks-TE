import sys
import socket
import select

socketlist = []

def server():

	host = ''
	port = 2000
	
	serversock = socket.socket(socket.AF_INET, socket.SOCK_STREAM, 0)
	serversock.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
	
	serversock.bind((host,port))
	serversock.listen(10)
	
	socketlist.append(serversock)
	
	while 1:
		ready_to_read, ready_to_write, error = select.select(socketlist, [], [], 0)
		
		for sock in ready_to_read :
			if sock == serversock :
				newserversock, addr = serversock.accept()
				print str(addr) + "connected\n"
				socketlist.append(newserversock)
				msg = str(addr) + " entered our chatting room \n"
				broadcast(serversock, sock, msg)
			else :
				data = sock.recv(1024)
				msg = "\nclient says :" +data
				broadcast(serversock, sock, msg)
				
def broadcast(serversock, sock,msg):
	for sockt in socketlist :
		if sockt != serversock and sockt != sock :
			sockt.send(msg)
			
server()
