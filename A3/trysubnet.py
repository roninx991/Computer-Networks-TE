import os

address = raw_input("Enter address in CIDR notation: ")
CIDR = address.split("/")
octets1 = CIDR[0].split(".")
octets2 = CIDR[0].split(".")

netmask = []
n = int(CIDR[1])/8

for i in range(n):
	netmask.append(255)

x = int(CIDR[1])%8
mask = 0

for i in range(8-x, 8):
	mask += 2**i

if len(netmask) < 5:
	netmask.append(mask)
	
for i in range(len(netmask),5):
	netmask.append(0)
	
subnet = str(netmask[0]) + "." + str(netmask[1]) + "." + str(netmask[2]) + "." + str(netmask[3])
print subnet
print "Subnet Ranges are: "

octet = n
k = 0
for i in range(0,2**x):
	print "Group " + str(i)
	for j in range(0,4):
		if j == octet:
			octets1[j] = k
			octets2[j] = k + (2**(8-x)) - 1
		if j > octet:
			octets1[j] = '0'
			octets2[j] = '255'
	print str(octets1[0]) + "." + str(octets1[1]) + "." + str(octets1[2]) + "." + str(octets1[3]) + " to " + str(octets2[0]) + "." + str(octets2[1]) + "." + str(octets2[2]) + "." + str(octets2[3]) +"\n"
	k = k + (2**(8-x))
	
print "Now doing ifconfig\n"
os.system("ifconfig")
interface = raw_input("Enter interface name: ")
os.system("ifconfig " + interface + " " + address + " netmask " + subnet)
ping = raw_input("Enter ip address to ping: ")
os.system("ping -c 5 " + ping)
