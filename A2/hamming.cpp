#include<iostream>
#include<cstring>
#include<cmath>

using namespace std;

char* ErrorWord(char *dataword, char *errorword, int n)
{
	int flag, skip, count,k;
	for(int i = 0; i < n; i++)
	{
		flag = 1;
		skip = pow(2,i);
		k = 0;
		count = 0;
		for(int j = skip - 1; j < strlen(dataword); j++)
		{
			if(flag == 1 && dataword[j] == '1')
				count++;
			
			k++;
			if(k == skip)
			{
				k = 0;
				flag = flag == 1 ? 0 : 1;
			}
		}
		if(count % 2 == 1)
			errorword[i] = '1';
		else
			errorword[i] = '0';
	}
	errorword[n] = '\0';
	//cout<<"\n"<<dataword<<"\n";
	return errorword;
}
	
char* Encode(char *dataword, char *errorword)
{
	for(int i = 0; i < strlen(errorword); i++)
	{
		int x = pow(2,i)-1;
		dataword[x] = errorword[i];
	}
	return dataword;
}

int ErrPos(char *errorword)
{
	int n = 0;
	int l = strlen(errorword);
	for(int i = 0; i < l; i++)
	{
		n += pow(2,i) * ((int)errorword[i]-48);
	}
	return n;
}

int main()
{
	char data[30], dataword[100], recvword[100], errorword[30];
	cout<<"Enter data: ";
	cin>>data;
	
	int d,n = 0;
	
	d = strlen(data);
	//cout<<d;
	while(pow(2,n) <= d + n)
		n++;
	
	//cout<<n;
	int k = 0, l = 0;
	for(int i = 0; i < d+n; i++)
	{
		if(i == pow(2,k)-1)
		{
			dataword[i] = '0';
			k++;
		}
		else
		{
			dataword[i] = data[l];
			l++;
		}
	}
	dataword[d+n] = '\0';
	cout<<"\n"<<dataword<<"\n";
	ErrorWord(dataword, errorword, n);
	cout<<"\n"<<errorword<<"\n";
	Encode(dataword, errorword);
	cout<<"\n"<<dataword<<"\n";
	
	cout<<"\nEnter received dataword: ";
	cin>>recvword;
	
	ErrorWord(recvword, errorword, n);
	cout<<"\n"<<errorword<<"\n";	
	int err = ErrPos(errorword);
	if(err)
	{
		cout<<"Error is at position: "<<err;
		recvword[err-1] = recvword[err-1] == '1' ? '0' : '1';
	}
	cout<<"Received word should be: "<<recvword;
	return 0;
}
