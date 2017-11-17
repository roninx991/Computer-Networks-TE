#include<iostream>
#include<sstream>
#include<fstream>

using namespace std;

int main()
{
	string line,protocol;
	string cell[6];
	int choice;
	
	
	while(1)
	{
	
		cout<<"\nEnter choice \n 1.IP\n2.TCP\n3.UDP\n4.Ethernet\n";
		cin>>choice;
		
		if(choice ==1)
			protocol= "\"ICMPv6\"";
		else if(choice == 2)
			protocol = "\"TCP\"";
		else if(choice == 3)
			protocol = "\"UDP\"";
		else if(choice == 4)
			protocol = "\"ARP\"";
		else{
			cout<<"wrong choice entered\n";
			return 0;
		}

		ifstream data("ass7.csv");
		
		int count=0;
		while(getline(data,line))
		{
			stringstream linestream(line);

			getline(linestream, cell[0], ',');
			getline(linestream, cell[1], ',');
			getline(linestream, cell[2], ',');
			getline(linestream, cell[3], ',');
			getline(linestream, cell[4], ',');
			getline(linestream, cell[5], ',');
			
		
			if(cell[4]==protocol)
			{
				count++;
				cout<<"serial no. :"<<count<<"\nEpoch time :"<<cell[1]<<"\n Source :"<<cell[2]<<"\n Destination :"<<cell[3]<<"\nProtocol :"<<cell[4]<<"\n Length :"<<cell[5]<<endl;
				
			
			}
			
		
		
		
		}
		
			
	cout<<"No. of "<<protocol<<":"<<count;
	
	
	
	}


}
