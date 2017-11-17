# chat_client.py

import sys
import socket
import select
 
def chat_client():
    if(len(sys.argv) < 3 or len(sys.argv) > 3) :
        print 'Usage : python chat_client.py <hostname> <port>'
        sys.exit()

    host = sys.argv[1]
    port = int(sys.argv[2])
     
    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    s.settimeout(20)
     
    # connect to remote host
    try :
        s.connect((host, port))
    except :
        print 'Unable to connect'
        sys.exit()
     
    print 'Connected to remote host. You can start sending messages'
    sys.stdout.write('[Chat] ')
    sys.stdout.flush()
     
    while 1:
        socket_list = [sys.stdin, s]
         
        # Get the list sockets which are readable
        ready_to_read,ready_to_write,in_error = select.select(socket_list , [], [])
         
        for sock in ready_to_read:             
            if sock == s:
                # incoming message from remote server, s
                data = sock.recv(4096)
                if not data :
                    print '\nDisconnected from chat server'
                    sys.exit()
                else :
                    #print data
                    sys.stdout.write(data)
                    sys.stdout.write('[Me] ')
		    sys.stdout.flush()     
            
            else :
                # user entered a message
                msg = sys.stdin.readline()
                s.send(msg)
                sys.stdout.write('[Me] ')
		sys.stdout.flush() 

chat_client()

#=======================================================Optional==============================================================
#if __name__ == "__main__":

#    sys.exit(chat_client())


"""
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
				
				
				
client()"""
