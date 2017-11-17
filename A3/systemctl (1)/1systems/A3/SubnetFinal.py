import os
import math

# This function returns true if magnitude of value lies within lower and higher bound, else false...
def inBetween (lowerBound, higherBound, value) :
	return True if value >= lowerBound and value <= higherBound else False
	

# Checks the IP values and returns the Tuple of class, default subnet and a value for CIDR Calculations...
# Doesn't work for class D and E
def returnClass (IP) :
	# If the first value is between 0-127, then class A
	if inBetween (0, 127, IP[0]) :
		return ['A', "255.0.0.0", 1]
	# If the first value is between 128-191, then class B
	elif inBetween (128, 191, IP[0]) :
		return ['B', "255.255.0.0", 2]
	# If the first value is between 192-223, then class C
	elif inBetween (192, 223, IP[0]) :
		return ['C', "255.255.255.0", 3]
		
# Returns true if the IP address is valid or not...
def isValidIPAddress (IP) :
	# Checks whether all the values of each section lies within 0-255
	if inBetween(0, 255, IP[0]) and inBetween(0, 255, IP[1]) and inBetween(0, 255, IP[2]) and inBetween(0, 255, IP[3]) :
		return True
	
	# If true, returns true, else returns false...
	return False

# Defines/shows the range of the groups divided...	
def subnetRanges (subnet, IPClass, number_of_subnet, group) :

	#############################################################################
	# Number of divisions according to the class and number of subnets...
	# eg : For class A : 
	# 		if number_of_subnet = 4, then,
	#		number of division = 2^24/4 = 16777216/4 = 4194304.
	# 		i.e., a group has 4194304 networks...
	#		subnet = 255.192.0.0
	#	   For same class :
	#		if number_of_subnet = 131072 (2^17), then,
	#		number of division = 2^24/131072 = 16777216/131072 = 128.
	# 		i.e., a group has 4194304 networks...
	#		subnet = 255.255.255.128
	#############################################################################
	
	# div : holds the number of network a group has...
	div = 256**(4-group) / number_of_subnet
	# if the IP class belongs to C, then,
	if IPClass == "C" :	
		# print the range of the given IP addresses which belongs to class C...
		for x in range (0, number_of_subnet) :
			# Denotes the group x+1, prints the group number, ending with colon,...
			print("Group " + str(x+1) + " : " ) # note : this comma is compulsory to make a space instead of new line..
			# Denotes the starting range of the (x+1)th group
			print(str(subnet[0]) +"."+ str(subnet[1])+"." + str(subnet[2])+"." + str(div * x))
			# Denotes the end range of the group...
			print("     to\n" + str(subnet[0])+"." + str(subnet[1])+"." + str(subnet[2])+"." + str(div * (x+1)-1 ))
			print("\n")
			
	elif IPClass == "B" :	
		# print the range of the given IP addresses which belongs to class B...
		for x in range (0, number_of_subnet) :
			# print the range of the given IP addresses which belongs to class B...
			print("Group " + str(x+1) + " : ")
			# Denotes the starting range of the (x+1)th group
			print(str(subnet[0]) +"."+ str(subnet[1])+"." + str(div * x / 256) + "." + str((div * x) % 256))
			# Denotes the end range of the group...
			print("     to\n" + str(subnet[0])+"." + str(subnet[1])+"." +  str((div * (x+1)-1)/256) + "." + str(((div * (x+1)-1)% 256))) 
			print("\n")
	else :
		# print the range of the given IP addresses which belongs to class A...
		for x in range (0, number_of_subnet) :
			# Group number
			print("Group " + str(x+1) + " : ")
			# Starting range
			print(str(subnet[0]) +"."+ str(div*x/65536)+"." + str(int(div*x/256)%256) + "." + str((div * x) % 256))
			# End range...
			print("     to\n" + str(subnet[0])+"." + str((div*(x+1)-1)/65536)+"." +  str(int((div*(x+1)-1)/256)%256) + "." + str(((div * (x+1)-1)% 256))) 
			print("\n")
			
			
# Function to print IP :
def printIP (IP) :
	return str(IP[0])+"."+str(IP[1])+"."+str(IP[2])+"."+str(IP[3])
	
	
	
######## Main Starts Here ########
choice = 'y'
while choice == 'y' or choice == 'Y' :
	# Takes the IP address of the machine and splits in an individual
	# Integers as an arrayList...
	IP = map (int, raw_input("Enter your IP address : ").split(".")) 

	# If the Entered IP address is valid, then execute the program
	if isValidIPAddress (IP) :

		# Returns the triplet of the class with default subnet and a number...
		# This number will help in calculating CIDR number...
		IPClass = returnClass (IP)
	
		# IPClass[0] : Class of your IP
		# IPClass[1] : Default Subnet
		# IPClass[2] : Number for CIDR calculations...
	
		print("Class of your IP : " + IPClass[0])
		print("Default Subnet of given IP : " + IPClass[1])
	
		# Takes the input of the subnet masks...
		# Best suggested to have input in power of 2...
		numberSubnets = int(raw_input("Enter the number of subnet masks : "))
	
		# subnetCal : To calculate the number of bits that must be set in default subnet...
		# Eg : for subnet 255.255.255.0 and numberSubnets = 4,
		# subnetCal = (log2(4)) = 2...
		# Therefore, two MSB bits of the last byte in default subnets should be set...
		# therefore, subnet after giving mask : 255.255.255.192 
		subnetCal, sum = int(math.log(numberSubnets, 2)), 0
	
		# For loop to set the MSB bits...
		for x in range (0, subnetCal%8) :
			sum += 2**(7-x)
		
		# CIDR : The IPClass[2] defines how many times the figure 255 comes
		# and using this, we'll store the number of bits that are set in the default subnet
		# This is useful in CIDR notation... 
		CIDR = 8*(IPClass[2])+subnetCal

		# *Important* : Evaluating the subnet for the given IP and group... #
		#############################################################################
		# For larger subdivision of networks, like dividing class A in 65536 parts,
		# following algorithm will determine how to set the subnet masks...
		# Eg : for IP : 10.10.15.20,
		# Default subnet : 255.0.0.0
		# If number of networks : 65536, then subnetCal = log2(65536) = 16
		# Therefore, one needs to set all the 16 bits...
		# Therefore, subnet for network is 255.255.255.0
		#############################################################################
	
		#############################################################################
		# limit : Calculates number of 255's does the default subnet masks required  
		# to be replaced...
		# eg: for above example, subnetCal = 16
		# therefore, limit = 2, i.e., replace the default subnet 255.0.0.0 
		# 2 times to get 255.255.255.0
		#############################################################################
		limit = int(subnetCal/8)
		for x in range (0, limit) :
			IPClass[1] = IPClass[1].replace("0", str(255), 1)
		# The remaining remainder to set the MSB 8 bits of zeroes...
		IPClass[1] = IPClass[1].replace("0", str(sum), 1)

		# For function subnetRanges, 
		# Argument 1 : your IP address...
		# Argument 2 : class of your IP...
		# Argument 3 : number of subnets that you've entered
		# Argument 4 : the number that helped in CIDR notation to find out
		#				total network in a particular group...
		subnetRanges (IP, IPClass[0], numberSubnets, IPClass[2])
	
		# Prints the subnet mask of your IP and
		print("The Subnet mask is : " + IPClass[1])
		# Prints the CIDR notation for your network...
		print("CIDR Notation : " + printIP(IP) + "/" + str(CIDR))

		print("########### Opening the terminal commands ############")
		os.system("ifconfig")

		os.system("ping -c 5 " + raw_input("Enter the IP address to PING : "))
	
		choice = raw_input("Do you want to continue ? (Y/N) : ")

