from __future__ import print_function
import os


cidr = raw_input("Enter CIDR :")

[address, bits] = cidr.split('/')

print ("The entered ip address is: " + address) 
print ("No. of significant bits in the address is: " + bits)

[addr1,addr2,addr3,addr4] = address.split('.')


#if int(addr1)>=0 and int(addr1)<=127 :
#	print "\nThe IP address belongs to class A "
#	print "Default subnetmask of class A is 255.0.0.0" 
#if int(addr1)>=128 and int(addr1)<=191 :
#	print "\nThe IP address belongs to class B "
#	print "Default subnetmask of class B is 255.255.0.0"
#if int(addr1)>=192 and int(addr1)<=223 :
#	print "\nThe IP address belongs to class C "
#	print "Default subnetmask of class C is 255.255.255.0"

addedbits = int(bits)%8
no_ofsubnets = 2**addedbits
addedmask = 0
run = 8- addedbits
temp=0

if int(bits) <= 8 :
	
	for i in range (0, addedbits):
		addedmask += 2**(7-i)
	netmask = str(addedmask) + ".0.0.0"
	print ("\nNetmask of given IP is: "+ netmask)
	print ("\n Subnet ranges are :")
	for i in range (0, no_ofsubnets):
		
		temp1=0
		print (str(temp)+ '.' +str(temp1) +'.' + str(temp1) + '.' +str(temp1),end='') 
		temp += 2**run
		temp1=255
		print (" to \n" + str(temp-1) + '.' +str(temp1) +'.' + str(temp1) + '.' +str(temp1) +"\n\n")
		
if int(bits) > 8 and int(bits) <=16 :
	
	for i in range (0, addedbits):
		addedmask += 2**(7-i)
	netmask = "255" +'.'+ str(addedmask)+ ".0.0"
	print ("\nNetmask of given IP is: "+ netmask)
	print ("\n Subnet ranges are :")
	for i in range (0, no_ofsubnets):

		temp1=0
		print (addr1+ '.' +str(temp) +'.' + str(temp1) + '.' +str(temp1),end='') 
		temp += 2**run
		temp1=255
		print (" to \n" + addr1 +'.'+ str(temp-1)+'.'+ str(temp1) + '.' +str(temp1) +"\n\n")

if int(bits) > 16 and int(bits) <=24 :
	
	for i in range (0, addedbits):
		addedmask += 2**(7-i)
	netmask = "255.255."+ str(addedmask)+".0"
	print ("\nNetmask of given IP is: "+ netmask)
	print ("\n Subnet ranges are :")
	for i in range (0, no_ofsubnets):

		temp1=0
		print (addr1+ '.' +addr2 +'.' + str(temp) + '.' +str(temp1),end='') 
		temp += 2**run
		temp1=255
		print (" to \n" + addr1 +'.'+ str(addr2)+'.'+ str(temp-1) + '.' +str(temp1) +"\n\n")
		

if int(bits) > 24 and int(bits) <=32 :
	
	for i in range (0, addedbits):
		addedmask += 2**(7-i)
	netmask = "255.255.255."+ str(addedmask)
	print ("\nNetmask of given IP is: "+ netmask)
	print ("\n Subnet ranges are :")
	for i in range (0, no_ofsubnets):

		temp1=0
		print (addr1+ '.' +addr2 +'.' + addr3 + '.' +str(temp),end='') 
		temp += 2**run
		temp1=255
		print (" to \n" + addr1 +'.'+ addr2+'.'+ addr3 + '.' +str(temp-1) +"\n\n")


print ("\n\nNow doing ifconfig\n\n")
#os.system("ifconfig")
#print ("Enter the given ip address and netmask generated\n"
os.system("ifconfig en0 "+ address +" " + netmask)
print("check from ifconfig now...\n")
os.system("ifconfig")
ip=raw_input("enter the ip address to ping ")
os.system("ping -c 5 " + ip)	
		
