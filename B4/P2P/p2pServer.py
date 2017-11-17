
import socket
import sys

HOST = ''              # Symbolic name meaning all available interfaces
BUFFER = 4096
PORT = 5001


def p2p_server():
   
    server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    server_socket.bind((HOST,PORT))
    server_socket.listen(1)

    print "Chat server started on port " + str(PORT) 
    conn, addr =  server_socket.accept()
    print "Connected by ",addr
    while 1:
	data = conn.recv(BUFFER)
	if not data :
		print '\nDisconnected from chat server'
		sys.exit()
	else :
	      	print '[Client]: ' + str(data)  
		msg = raw_input("[Server]: ")
		if msg == 'q':
			sys.exit()
		conn.send(msg)

    conn.close()

if __name__ == "__main__":

    sys.exit(p2p_server())
