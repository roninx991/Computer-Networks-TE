import sys
import socket
import select

socketlist = []
def Client():
	host = sys.argv[1]
	port = int(sys.argv[2])
	
	client = socket.socket(socket.AF_INET,socket.SOCK_STREAM,0)
	
	client.connect((host,port))
	
	while True:
		socketlist = [sys.stdin,client]
		
		ready_to_read,ready_to_write,error = select.select(socketlist,[],[],0)
		
		for sock in socketlist:
			if sock == client:
				data = sock.recv(1024)
				if data:
					print data
				else:
					"Disconnected"
					
			else:
				msg = raw_input("Client: ")
				client.send(msg)
				
Client()
