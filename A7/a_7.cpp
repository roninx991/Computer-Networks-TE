#include <iostream>
#include <sstream>
#include <fstream>
#include <string>

using namespace std;

int main()
{
	
	int count,i;
	string line;
	int choice;
    string protocol;

    
    while(1){
        ifstream data("sample.csv");
        count=0;
	cout<<"Enter protocol:";
	cout<<"\n1.IP \n2.TCP \n3.ARP\n4.UDP\n";
	cin>>choice;


	
	if(choice==1)
		protocol="\"ICMPv6\"";
	else if(choice==2)
		protocol="\"TCP\"";
	else if(choice==3)
		protocol="\"ARP\"";
	else if(choice==4)
		protocol="\"UDP\"";
	else
	{
		cout<<"\nInvalid choice...Exiting..";
		return 0;
	}

	int t=0;

	while(getline(data,line))
	{
		stringstream linestream(line);
		string cell[8];
		
		getline(linestream,cell[0],',');
		getline(linestream,cell[1],',');
		getline(linestream,cell[2],',');
		getline(linestream,cell[3],',');
		getline(linestream,cell[4],',');
		getline(linestream,cell[5],',');
		//getline(linestream,cell[6],',');
		//getline(linestream,cell[7],',');
        
        if((cell[4].compare(protocol))==0)
		{
			count++;
			cout<<"\n\nSr. No. #"<<count<<"\nTime :\t"<<cell[1]<<"\nSource :\t"<<cell[2]<<"\nDestination :\t"<<cell[3]<<"\nProtocol :\t"<<cell[4]<<"\nLength :\t"<<cell[5]<<"\n\n";	
		}
		     
		}
		cout<<"No. of "<<protocol<<" packets:\t"<<count;
  
    }
}
