#include<iostream>
#include<strings.h>
#include<math.h>

using namespace std;

class Hamming
{

public:
	char dataword[20],codeword[50],recvword[50];
	int parity,datalen,codelen;
	
	Hamming(){
		parity=datalen=codelen=0;
	}
	void getdata()
	{
		cout<<"enter the data word :";
		cin>>dataword;
	}
	
	void getparity()
	{
		
		datalen= strlen(dataword);
		while(pow(2,parity) < datalen+parity+1)
			parity++;
			
		codelen=datalen+parity;
		int k=0,j=0;
		for(int i=1;i<=codelen;i++)
		{
			if(i==pow(2,k)){
				codeword[i-1]='0';
				k++;
			}else{
				codeword[i-1]=dataword[j];
				j++;
			}
		}
		codeword[codelen]='\0';
		cout<<codeword<<endl;
	
	}
	
	void calparity()
	{
		for(int i=0;i<parity;i++)
		{
			int flag=1;int count =0;int skip=0;
			int step=pow(2,i);
			for(int j=step-1;j<codelen;j++)
			{
				if(flag==1)
				{
					if(codeword[j]=='1')
						count++;
				}
				skip++;
				if(skip==step)
				{
					skip=0;
					if(flag==1)
						flag=0;
					else
						flag=1;
					
				}
			
			}
			if(count%2!=0)
				codeword[step-1]='1';
		
		}
		
		cout<<"\nthe codeword generated is: "<<codeword; 
		
		codeword[codelen]='0';
		for(int i=0;i<codelen;i++)
		{
			if(codeword[codelen]==codeword[i])
				codeword[codelen]='0';
			else
				codeword[codelen]='1';
		}
		codeword[codelen+1]='\0';
		cout<<"\ngenerated codeword with even parity :"<<codeword;
	
	
	}

	void recvdata()
	{
		cout<<"\n enter the received data :"<<endl;
		cin>>recvword;
	}

	void checksum()
	{
		int checkparity='0';
		for(int i=0;i<codelen;i++)
		{
			if(checkparity==recvword[i])
				checkparity='0';
			else
				checkparity='1';
		
		}
		if(checkparity==codeword[codelen])
			cout<<"\n Data received succesfully !";
		else
		{
			cout<<"\n data error !!";
			char error[20];
			
			for(int i=0;i<parity;i++)
			{
			
				int step=pow(2,i);int flag=1,skip=0,count=0;
				for(int j=step-1;j<codelen;j++)
				{
					if(flag==1)
					{
						if(recvword[j]=='1')
							count++;	
					}
					skip++;
					if(skip==step)
					{
						skip=0;
						if(flag==1)
							flag=0;
						else
							flag=1;
						
					}		
				
				
				}
				
				if(count%2!=0)
					error[i]='1';
				else
					error[i]='0';
						
			}
			int errsum=0;
			cout<<"\nError is at: ";
			for(int i=parity-1;i>=0;i--)
			{
				cout<<error[i];
			
			}
			for(int i=parity-1;i>=0;i--)
			{
				if(error[i]=='1')
				{
					errsum += pow(2,i)*(int(error[i]-48));
				}
			
			}
			cout<<"\n error position :"<<errsum;
			
			
		
		
	
		}
	
	
	
	}





};

int main()
{
	Hamming obj;
	obj.getdata();
	obj.getparity();
	obj.calparity();
	obj.recvdata();
	obj.checksum();





}
