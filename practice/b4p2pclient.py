import socket
import sys
def Client():
	host = sys.argv[1]
	port = int(sys.argv[2])
	
	client = socket.socket(socket.AF_INET,socket.SOCK_STREAM)
	client.settimeout(2000)

	client.connect((host,port))
	
	while True:
		msg = raw_input("Your message: ")
		
		client.send(msg,0)
		
		data = client.recv(1024)
		
		if not data:
			print "Disconnected"
			sys.exit(0)
		
		print "Server says: " + data
Client()
				
