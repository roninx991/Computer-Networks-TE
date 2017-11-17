#include<iostream>
#include<cstring>
#include<sstream>
#include<fstream>
#include<cstdlib>

using namespace std;


int main()
{
	int ch;
	int count;
	string protocol,value;
	
	
	while(1)
	{
		cout<<"Choose option:\n1.TCP\n2.IP\n3.UDP\n4.DHCP\n5.Exit\n\n";
		cin>>ch;
		ifstream file("sample.csv");
		switch(ch)
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
		}
		count = 0;
		while(getline(file,value))
		{
			string str[7];
			stringstream linestream(value);

			getline(linestream,str[0],',');
			
			getline(linestream,str[1],',');
			
			getline(linestream,str[2],',');
			
			getline(linestream,str[3],',');
			
			getline(linestream,str[4],',');
			
			getline(linestream,str[5],',');
			
			getline(linestream,str[6],',');
			
			if(str[4].compare(protocol)==0)
			{
				cout<<"\nSr. No. #"<<count<<"\nTime: "<<str[1]<<"\nSource: "<<str[2]<<"\nDestination: "<<str[3]<<"\nProtocol: "<<str[4]<<"\nLength: "<<str[5]<<"\n\n";
				count++;
			}
		}
	}
	return 0;
}
