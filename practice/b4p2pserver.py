import socket
import sys

def Server():
	host = ''
	port = 2001
	
	server = socket.socket(socket.AF_INET,socket.SOCK_STREAM)
	server.bind((host,port))
	
	server.listen(1)
	
	conn,addr = server.accept()
	
	while True:
		data = conn.recv(1024)
		
		if not data:
			print "Disconnected"
			sys.exit(0)
		
		print "Client says: " + data

		msg = raw_input("Your message: ")
		
		conn.send(msg,0)
		
Server()

