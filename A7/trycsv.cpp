#include<iostream>
#include<fstream>
#include<cstring>
#include<cstdlib>
#include<sstream>

using namespace std;

int main()
{
	int option;
	int count=0;
	string protocol;
	string value;
	
	while(1)
	{
		cout<<"\nChoose protocol number or exit:\n1.TCP\n2.IP\n3.UDP\n4.DHCP\n5.Exit\n\n";
		cin>>option;
		ifstream file("sample.csv");

		switch(option)
		{
			case 1:
				protocol = "TCP";
				break;
			case 2:
				protocol = "IP";
				break;
			case 3:
				protocol = "UDP";
				break;
			case 4:
				protocol = "DHCPv6";
				break;
			case 5:
				exit(0);
				break;
			default:
				cout<<"Choose correct option!"; 
		}
		
		while(getline(file,value))
		{
			stringstream line(value);
			string str[7];
			
			getline (line, str[0], ',');
			
			getline (line, str[1], ',');
			
			getline (line, str[2], ',');
			
			getline (line, str[3], ',');
			
			getline (line, str[4], ',');
			
			getline (line, str[5], ',');
			
			getline (line, str[6], ',');
			
		
			if(str[4].compare(protocol) == 0)
			{
				count++;
				cout<<"\nSr. No. #"<<count<<"\nTime: "<<str[1]<<"\nSource: "<<str[2]<<"\nDestination: "<<str[3]<<"\nProtocol: "<<str[4]<<"\nLength: "<<str[5]<<"\n\n";
			}
		}
		count = 0;
	}
	return 0;
	
}
