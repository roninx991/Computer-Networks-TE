import os

cidr = raw_input("enter cidr :")

addr, bits = cidr.split('/')

addr1,addr2,addr3,addr4 = addr.split('.')

print "\nThe given address is :" + addr
print "No. of active bits :" + bits

addedbits = int(bits)%8
run = 8-addedbits
numofsubnets = 2**addedbits
addedmask=0

print "Total subnets :" + str(numofsubnets)

if int(bits)<8 and int(bits)>=0 :
	for i in range(0, addedbits):
		addedmask += 2**(7-i)
	#if(addedbits==0):
	#	addedmask=255 
	netmask =str(addedmask) +".0.0.0"
	print "\n subnet mask :" + netmask
	print "\n Subnet ranges are :\n"
	temp = 2**run
	temp1=0
	for i in range (0, numofsubnets) :
		print str(temp1) +".0.0.0 to "+str(temp-1)+".255.255.255"
		temp1=temp
		temp =temp+ 2**run

if int(bits)<16 and int(bits)>=8 :
	for i in range(0, addedbits):
		addedmask += 2**(7-i)
	netmask= "255." +str(addedmask) +".0.0"
	print "\n subnet mask :" + netmask
	print "\n Subnet ranges are :\n"
	temp = 2**run
	temp1=0
	for i in range (0, numofsubnets) :
		print addr1+"." +str(temp1)+".0.0 to " +addr1 + "." +str(temp-1)+".255.255"
		temp1=temp
		temp =temp+ 2**run
		
if int(bits)<24 and int(bits)>=16 :
	for i in range(0, addedbits):
		addedmask += 2**(7-i)
	netmask = "255.255." +str(addedmask) +".0"
	print "\n subnet mask :" + netmask
	print "\n Subnet ranges are :\n"
	temp = 2**run
	temp1=0
	for i in range (0, numofsubnets) :
		print addr1+"."+addr2+"." +str(temp1)+".0 to " +addr1 +"."+addr2+ "." +str(temp-1)+".255"
		temp1=temp
		temp =temp+ 2**run
	
if int(bits)<=32 and int(bits)>=24 :
	for i in range(0, addedbits):
		addedmask += 2**(7-i)
	if(addedbits==0)
		addedmask=255
	netmask = "255.255.255." +str(addedmask)
	print "\n subnet mask :" +netmask
	print "\n Subnet ranges are :\n"
	temp = 2**run
	temp1=0
	for i in range (0, numofsubnets) :
		print addr1+"."+addr2+"."+addr3+"." +str(temp1)+" to "  +addr1 +"."+addr2+ "." +addr3+"."+str(temp-1)
		temp1=temp
		temp =temp+ 2**run
		
		
print "\n\n Opening ifcongig"
os.system("ifconfig")
print "\n\n Changing System IP"
os.system("ifconfig en0 "+addr+" "+netmask)
os.system("ifconfig")
ip = raw_input("\n enter IP to ping :")
os.system("ping -c 5 "+ip)



 
