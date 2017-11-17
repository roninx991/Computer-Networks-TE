import sys
import select
import socket

socketlist =[]


def client():
	
	
	host = sys.argv[1]
	port = int(sys.argv[2])
	
	clientsock = socket.socket(socket.AF_INET, socket.SOCK_STREAM, 0)
	
	clientsock.connect((host,port))
	
	while 1:
		socketlist = [sys.stdin, clientsock]
		ready_to_read, ready_to_write, error = select.select(socketlist, [],[],0)
		for sock in ready_to_read :
			if sock == clientsock :
				data = clientsock.recv(1024)
				print data
			else:
				msg = raw_input()
				clientsock.send(msg)
				
				
				
client()
