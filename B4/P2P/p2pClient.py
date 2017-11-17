import socket
import sys

def p2p_client():

	host = sys.argv[1] 
	port = int(sys.argv[2])

	s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
	s.settimeout(2000)

	s.connect((host, port))

	while 1:
		msg = str(raw_input('[Client]: '))
		if msg == 'q':
			sys.exit()
		s.send(msg)
		data = s.recv(4096)
		if not data :
			print '\nDisconnected from chat server'
			sys.exit()
		else :
		      	#print data
			print '[Server]: ' + str(data)
			

	conn.close()

if __name__ == "__main__":

     sys.exit(p2p_client())
