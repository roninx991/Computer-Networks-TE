import sys
import socket

def client():
	host = sys.argv[1]
	port = int(sys.argv[2])
	
	clientsock = socket.socket(socket.AF_INET, socket.SOCK_STREAM, 0)
	
	clientsock.connect((host,port))
	
	while 1:
		msg = raw_input("\nSend message :")
		clientsock.send(msg)
		
		data = clientsock.recv(1024)
		print "server says :" +data
		
client()
