import os
import math

#Returns true if the values lies within the range...
def inBetween (left, right, value) :
	return True if value >= left and value <= right else False

#returns the equivalent binary for the number...
def numberToBinary(number) :
	return '{0:08b}'.format(number)

#Returns the class of the IP address along with it's subnet...
def Class(IP) :
	if inBetween(0, 127, IP[0]) :
		return ["A", "255.0.0.0", 1]
	elif inBetween(128, 191, IP[0]) :
		return ["B", "255.255.0.0", 2]
	elif inBetween(192, 223, IP[0]) :
		return ["C", "255.255.255.0", 3]

#Print the ranges of the class from the required number of subnets...
def subnetRanges (subnet, IPClass, number_of_subnet, group) :
	div = 256**(4-group) / number_of_subnet
	if IPClass == "C" :	
		for x in range (0, number_of_subnet) :
			print("Group " + str(x+1) + " : " + str(subnet[0]) +"."+ str(subnet[1])+"." + str(subnet[2])+"." + str(div * x) + "  to  " + str(subnet[0])+"." + str(subnet[1])+"." + str(subnet[2])+"." + str(div * (x+1)-1 )) 
	elif IPClass == "B" :	
		for x in range (0, number_of_subnet) :
			print("Group " + str(x+1) + " : " + str(subnet[0]) +"."+ str(subnet[1])+"." + str(div * x / 256) + "." + str((div * x) % 256)+ "  to  " + str(subnet[0])+"." + str(subnet[1])+"." +  str((div * (x+1)-1)/256) + "." + str(((div * (x+1)-1)% 256))) 
	else :
		for x in range (0, number_of_subnet) :
			print("Group " + str(x+1) + " : " + str(subnet[0]) +"."+ str(div*x/65536)+"." + str(int(div*x/256)%256) + "." + str((div * x) % 256)+ "  to  " + str(subnet[0])+"." + str((div*(x+1)-1)/65536)+"." +  str(int((div*(x+1)-1)/256)%256) + "." + str(((div * (x+1)-1)% 256))) 
						
def printIP (IP) :
	return str(IP[0])+"."+str(IP[1])+"."+str(IP[2])+"."+str(IP[3])
	
def isValidIPAddress(IP) :
	return True if inBetween(0, 255, IP[0]) and inBetween(0, 255, IP[1]) and inBetween(0, 255, IP[2]) and inBetween(0, 255, IP[3]) else False 

choice = "Y"
while choice == "Y" or choice == "y" :	
	#Splits the IP address into a list of integers...
	IP = list(map(int, raw_input("Enter the I.P. address : ").split(".")))

	if len(IP) != 4 and isValidIPAddress (IP) :
		print ("You have entered an Invalid IP address")
	else :	
		#If a valid address, retrieve the class and perform following operations
		classSubnet = Class(IP)

		print("IP class : " + classSubnet[0])
		print("Default Mask : " + classSubnet[1])

		number_of_subnets = int(raw_input("Enter the number of Subnets : "))

		# Helps in calculating the equivalent subnet of the IP...
		subnetCal, sum = int(math.log(number_of_subnets, 2)), 0
		
		for x in range (0, subnetCal%8) :
			sum += 2**(7-x)
		CIDR = 8*(classSubnet[2])+subnetCal
		
		#Prints the CIDR notation for the current IP address...
		print("CIDR Notation : " + printIP(IP) + "/" + str(CIDR))
		#Converts the default subnets according to the number of subnets provided...
		limit = int(CIDR/8-1)
		for x in range (0, limit) :
			classSubnet[1] = classSubnet[1].replace("0", str(255), 1)
		classSubnet[1] = classSubnet[1].replace("0", str(sum), 1)
		
		subnetArr = list(map(int, classSubnet[1].split(".")))

		subnetRanges(IP, classSubnet[0], number_of_subnets, classSubnet[2])
		print(subnetCal, numberToBinary(sum))
		print("The Subnet mask is : " + classSubnet[1])
		print("CIDR Notation : " + printIP(IP) + "/" + str(8*(classSubnet[2])+subnetCal))

		####################Demonstration of the IP address and subnet mask by pinging to other network####################
		print("###########Opening the terminal commands############")
		os.system("ifconfig")

		os.system("ping -c 8 " + raw_input("Enter the IP address to PING : "))
	choice = raw_input("Do you want to continue ? (Y/n) : ")

