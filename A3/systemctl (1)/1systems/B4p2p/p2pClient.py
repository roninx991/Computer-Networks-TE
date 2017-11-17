
import socket
import sys

def p2p_client():
   if(len(sys.argv) < 2) :
        print 'Usage : python p2pClient.py hostname port'
        sys.exit()


   host = sys.argv[1] 
   port = int(sys.argv[2])
     
   s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
   s.settimeout(20)
     
   s.connect((host, port))
   while 1:
        sys.stdout.write('[ShuB] '); sys.stdout.flush() 
        msg = sys.stdin.readline()
        s.send(msg)
        data = s.recv(4096)
        if not data :
                    print '\nDisconnected from chat server'
                    sys.exit()
        else :
              #print data
	      sys.stdout.write('Server says: '); sys.stdout.flush() 
              sys.stdout.write(data)
        

   conn.close()

if __name__ == "__main__":

     sys.exit(p2p_client())
