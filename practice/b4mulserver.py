import sys
import socket
import select

socketlist = []
def Server():
	
	
	host = ''
	port = 2000
	
	server = socket.socket(socket.AF_INET, socket.SOCK_STREAM,0)
	server.setsockopt(socket.SOL_SOCKET,socket.SO_REUSEADDR,1)
	server.bind((host,port))
	
	server.listen(10)
	
	socketlist.append(server)
	
	while True:
		ready_to_read,ready_to_write,error = select.select(socketlist,[],[],0)
		
		for sock in ready_to_read:
			if sock == server:
				conn,addr = server.accept()
				print str(addr) + "is connected"
				socketlist.append(conn)
				
			else:
				data = sock.recv(1024)
				if data:
					msg = str(sock.getpeername()) + " says: " + data
					broadcast(server,sock,msg)
					
def broadcast(server,sock,msg):
	for s in socketlist:
		if s != server and s != sock:
			s.send(msg,0)
			
Server()
