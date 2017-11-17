import os

address = raw_input("Enter IP adrees in CIDR notation: ")
CIDR = address.split("/")
octets1 = CIDR[0].split(".")
octets2 = CIDR[0].split(".")

n = int(CIDR[1])/8
x = int(CIDR[1])%8

octet = 0
mask = []

for i in range(8-x,8):
	octet += 2**i
	
for i in range(4):
	if i < n:
		mask.append("255")
	elif i == n:
		mask.append(str(octet))
	else:
		mask.append("0")
		
netmask = mask[0] + "." + mask[1] + "." + mask[2] + "." + mask[3]

print "Netmask is: " + netmask
k = 0
print "Subnet Ranges: "
for i in range(2**x):
	print "Group " + str(i)
	for i in range(4):
		if i == n:
			octets1[i] = k
			octets2[i] = k + 2**(8-x)-1
		elif i > n:
			octets1[i] = 0
			octets2[i] = 255
			
	print str(octets1[0]) + "." + str(octets1[1]) + "." + str(octets1[2]) + "." + str(octets1[3]) + " to " + str(octets2[0]) + "." + str(octets2[1]) + "." + str(octets2[2]) + "." + str(octets2[3])
	k = k + 2**(8-x)
	
print "Now doing ifconfig"

os.system("ifconfig")
inter = raw_input("Enter interface: ")
os.system("ifconfig " + inter + " " + CIDR[0] + " netmask " + netmask)
os.system("ifconfig")
ip = raw_input("Enter IP you want to ping : ")
os.system("ping -c 5 " + ip)  
