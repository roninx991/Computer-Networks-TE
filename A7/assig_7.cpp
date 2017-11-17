#include<iostream>
#include<fstream>
#include<cstring>
#include<cstdlib>
#include<sstream>

using namespace std;



int main()
{
	string proto; 
	int n;
	string value;
	int count = 0;
	
	while(1)
	{
		cout<<"\n\n1.TCP \n2.IP \n3.UDP \n4.Ethernet\n5.Exit\nEnter protocol no-:";
		cin>>n;
		ifstream file("sample.csv");
			
		switch(n)
		{
		
			case 1:
			proto = "TCP";
				break;
			
			case 2:
			proto = "IP";
			
				break;
		
			case 3:
			proto = "UDP";
				break;
		
			case 4:
			proto = "DHCPv6";
				break;
		
			case 5:
				exit(1);
				break;
			
			default:
				cout<<"\nEnter valid choice!!";
			
		}
		while (getline(file,value))
		{
			stringstream linestream(value);		
			string str[7];

			getline (linestream, str[0], ',' );
			
			getline (linestream, str[1], ',' );
			
			getline (linestream, str[2], ',' );
			
			getline (linestream, str[3], ',' );
			
			getline (linestream, str[4], ',' );
			
			getline (linestream, str[5], ',' );
			
			getline (linestream, str[6], ',' );
			
			if((str[4].compare(proto))==0)
			{
				count++;
				cout<<"\n\nSr. No. #"<<count<<"\nTime :\t"<<str[1]<<"\nSource :\t"<<str[2]<<"\nDestination :\t"<<str[3]<<"\nProtocol :\t"<<str[4]<<"\nLength :\t"<<str[5]<<"\n\n";	
			}
			     
		}
		cout<<"No. of "<<proto<<" packets:\t"<<count;
	}
	return 0;
}


