#include<iostream>
#include<cstring>
#include<cmath>

using namespace std;

void ErrorWord(char* dataword,char* errorword,int n)
{
	int step,flag,count,k;
	for(int i=0;i<n;i++)
	{
		step = pow(2,i);
		flag = 1;
		count = 0;
		k = 0;
		for(int j = step-1;j<strlen(dataword);j++)
		{
			if(dataword[j] == '1' && flag == 1)
				count++;
			k++;
			if(k == step)
			{
				k = 0;
				flag = flag == 0 ? 1 : 0;
			}
		}
		if(count%2 == 0)
			errorword[i]='0';
		else
			errorword[i]='1';
	}
	errorword[n]='\0';
}
void DataWord(char* dataword,char* errorword,int n)
{
	int x;
	for(int i = 0; i< n;i++)
	{
		x = pow(2,i)-1;
		dataword[x] = errorword[i];
	}
}
int ErrorPos(char* errorword)
{
	int n = strlen(errorword);
	int x=0;
	for(int i =0;i<n;i++)
	{
		x += (((int)errorword[i])-48)*pow(2,i);
	}
	return x;
}
int main()
{
	char errorword[20],error[20],data[20],dataword[20],codeword[20];
	int k=0;
	int pos;
	cout<<"Enter data to be sent";
	cin>>data;
	
	int i=0,d = strlen(data);
	
	while(pow(2,i)< d + i + 1)
		i++;
	
	int r =0;
	for(int j=0;j<d+i;j++)
	{
		if(j == pow(2,k)-1)
		{
			dataword[j] = '0';
			k++;
		}
		else
		{
			dataword[j] = data[r];
			r++;
		}
	}
	ErrorWord(dataword,errorword,i);
	
	cout<<errorword;
	
	DataWord(dataword,errorword,i);
	
	cout<<dataword;
	
	cout<<"Enter received word: ";
	cin>>codeword;
	
	ErrorWord(codeword,error,i);
	
	cout<<error;
	
	pos = ErrorPos(error);
	
	cout<<pos;
	
	codeword[pos-1] = codeword[pos-1] == '0' ? '1':'0'; 
	cout<<codeword;
}
	
