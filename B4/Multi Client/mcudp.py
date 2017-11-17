import sys
import socket

def client():
	host = sys.argv[1]
	port = int(sys.argv[2])
	
	clientsock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
	
	clients = [sys.stdin, clientsock]
	while True:
		for s in clients:
			if s == clientsock:
				data = clientsock.recvfrom(4096)
				if not data:
					print "Disconnected from server"
					sys.exit()
				else:
					print data[0]
					print "[Client]: "
			else:
				msg = sys.stdin.readline()
				clientsock.sendto(msg, (host, port))
				print "[Client]: "
		
		
		
client()
