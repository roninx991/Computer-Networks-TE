import sys
import socket

def server():
	host = ''
	port = 2000
	
	serversock = socket.socket(socket.AF_INET, socket.SOCK_STREAM, 0)
	serversock.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
	
	serversock.bind((host,port))
	serversock.listen(1)
	
	newserversock,addr = serversock.accept()
	
	print "connected to :" + str(addr)
	while 1:
	
		data = newserversock.recv(1024)
		print "\nClient says : " +data
		
		msg = raw_input("\nsend message :")
		newserversock.send(msg)
		
		
server()
