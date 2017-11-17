import sys
import socket
import select

socketlist = []
def Server():
	host = ''
	port = 2000
	
	server = socket.socket(socket.AF_INET,socket.SOCK_STREAM,0)
	server.setsockopt(socket.SOL_SOCKET,socket.SO_REUSEADDR,1)
	server.bind((host,port))
	
	server.listen(10)
	socketlist.append(server)
	
	while True:
		ready_to_read,ready_to_write,error = select.select(socketlist,[],[],0)
		
		for sock in ready_to_read:
			if sock == server:
				client,addr = sock.accept()
				socketlist.append(client)
				msg = str(addr) + "joined the room"
				print msg
				broadcast(server,sock,msg)
				
			else:
				data = sock.recv(1024)
				broadcast(server,sock,data)
					
	server.close()

def broadcast(server,sock,msg):
	for s in socketlist:
		if s != server and s != sock:
			s.send(msg)
			
Server()
