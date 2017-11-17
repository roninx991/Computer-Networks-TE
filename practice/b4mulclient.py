import sys
import socket
import select

def Client():
	host = sys.argv[1]
	port = int(sys.argv[2])
	
	client = socket.socket(socket.AF_INET, socket.SOCK_STREAM,0)
	
	client.connect((host,port))
	
	socketlist = [sys.stdin,client]
	
	while True:
		ready_to_read,ready_to_write,error = select.select(socketlist,[],[],0)
		
		for sock in ready_to_read:
			if sock == client:
				data = client.recv(1024)
				print data
			else:
				msg = raw_input("Your msg: ")
				client.send(msg,0)	
				
Client()				
