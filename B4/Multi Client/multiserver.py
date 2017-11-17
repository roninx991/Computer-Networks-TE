# chat_server.py
 
import sys			#for terminal or sys args
import socket			#socket programming
import select			#package used for monitoring I/O operations for linux

HOST = '' 
SOCKET_LIST = []
RECV_BUFFER = 4096 
PORT = 9009

def chat_server():

#socket() - usage socket.socket(domain, type) returns socket object

    server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)			#AF_INET is for IPv4 address family && SOCK_STREAM is for TCP(use SOCK_DGRAM for UDP

#setsockopt() - usage socket.setsockopt(level, option name, value)

    server_socket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)			#Set the value of the given socket option

#bind() - usage socket_object.bind(address)

    server_socket.bind((HOST, PORT))							#Binds address to socket object. The socket object mustn't have already binded address

#listen() - usage socket_object.listen(backlog)

    server_socket.listen(10)								#Listen for connections made to the socket. 
 
    # add server socket object to the list of readable connections
    SOCKET_LIST.append(server_socket)
 
    print "Chat server started on port " + str(PORT)
 
    while 1:

        # get the list sockets which are ready to be read through select
        # 4th arg, time_out  = 0 : poll and never block

	#select() - usage select.select(lob[to be read from], lob[to be output to], lob[error check], timeout) returns 3 lists

        ready_to_read,ready_to_write,in_error = select.select(SOCKET_LIST,[],[],0)		
      
        for sock in ready_to_read:
            # a new connection request recieved
            if sock == server_socket:
 
		# Accept a connection. The socket must be bound to an address and listening for connections.
		# The return value is a pair (conn, address) where conn is a new socket object usable to send and receive data on the connection,
		# and address is the address bound to the socket on the other end of the connection.

                sockfd, addr = server_socket.accept()		

                SOCKET_LIST.append(sockfd)
                print "Client (%s, %s) connected" % addr
		print "hello there"
                 
                broadcast(server_socket, sockfd, "[%s:%s] entered our chatting room\n" % addr)
             
            # a message from a client, not a new connection
            else:
                # process data recieved from client, 
                try:
                    # receiving data from the socket.
                    data = sock.recv(RECV_BUFFER)
                    if data:
                        # there is something in the socket
                        broadcast(server_socket, sock, "\r" + '[' + str(sock.getpeername()) + '] ' + data)  
                    else:
                        # remove the socket that's broken    
                        if sock in SOCKET_LIST:
                            SOCKET_LIST.remove(sock)

                        # at this stage, no data means probably the connection has been broken
                        broadcast(server_socket, sock, "Client (%s, %s) is offline\n" % addr) 

                # exception 
                except:
                    broadcast(server_socket, sock, "Client (%s, %s) is offline\n" % addr)
                    continue

    server_socket.close()
    
# broadcast chat messages to all connected clients
def broadcast (server_socket, sock, message):
    for socket in SOCKET_LIST:
        # send the message only to peer
        if socket != server_socket and socket != sock :
            try :
                socket.send(message)
            except :
                # broken socket connection
                socket.close()
                # broken socket, remove it
                if socket in SOCKET_LIST:
                    SOCKET_LIST.remove(socket)

chat_server()
 
#===========================================Optional=========================================================
#if __name__ == "__main__":
    
#	sys.exit(chat_server()) 
"""
import sys
import socket
import select

socketlist = []

def server():

	host = ''
	port = 2000
	
	serversock = socket.socket(socket.AF_INET, socket.SOCK_STREAM, 0)
	serversock.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
	
	serversock.bind((host,port))
	serversock.listen(10)
	
	socketlist.append(serversock)
	
	while 1:
		ready_to_read, ready_to_write, error = select.select(socketlist, [], [], 0)
		
		for sock in ready_to_read :
			if sock == serversock :
				newserversock, addr = serversock.accept()
				print str(addr) + "connected\n"
				socketlist.append(newserversock)
				msg = str(addr) + " entered our chatting room \n"
				broadcast(serversock, sock, msg)
			else :
				data = sock.recv(1024)
				msg = "\nclient says :" +data
				broadcast(serversock, sock, msg)
				
def broadcast(serversock, sock,msg):
	for sockt in socketlist :
		if sockt != serversock and sockt != sock :
			sockt.send(msg)
			
server()"""
