import sys
import socket

clients = []

def server():
	host = ''
	port = 5000

	serversock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
	
	serversock.bind((host, port))
	
	
	while True:
		data, addr = serversock.recvfrom(4096)
		if addr not in clients:
			clients.append(addr)
		if not data:
			break
		broadcast(serversock, data, addr, clients)
		
		
		
def broadcast(serversock, data, addr, clients):
	
	data = "From " + str(addr) + ":" + data
	for c in clients:
		if c != addr:
			serversock.sendto(data, c)
		
server()
