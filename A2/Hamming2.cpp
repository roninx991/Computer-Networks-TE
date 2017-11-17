#include <iostream>
#include <cmath>
#include <cstring>

using namespace std;

class Hamming {
	char abc[64], data[71], receivedData[71], error[10];
	int dataLength, parityBit, errorPosition;

public:	
	Hamming() { dataLength = 0; parityBit = 0; errorPosition = 0; }
	
	void acceptData() {
		cout << "Enter the data : ";
		cin >> abc;	
		int loop = 0;
		dataLength = strlen(abc);
		while(pow(2, loop) < dataLength+loop+1)			//2^r <= d + r + 1
			loop++;

		parityBit = loop;					//parityBits = r
		int k = 0, ptr = 0;
		
		// Putting zero in parity positions p1,p2,p4 ....and so on
		
		for(int i = 1; i <= dataLength+parityBit; i++) {	
			if(i == pow(2, k)) {
				data[i-1] = '0';
				k++;
			}
			else 
				data[i-1] = abc[ptr++];					
		}
		data[dataLength+parityBit] = '\0';
		dataLength = dataLength+parityBit;			//d = d + r
	}	
	
	void calculateParity () {
		/*for(int i = 0; i < parityBit; i++) {
			int temporary = pow(2, i);
			
			for(int j = temporary; j <= dataLength; j++) {
				if(((j - temporary) / temporary) % 2 == 0 )
					data[temporary-1] = data[temporary-1] == data[j-1] ? '0' : '1';	
			} 
		}*/
		int step = 0, flag = 0, k = 0;int p = 0;
		for(int i = 0; i < parityBit; i++)
		{
			flag = 1;
			step = pow(2,i);
			p = 0;
			for(int j=step-1; j < dataLength; j++)
			{
				if(flag == 1)
				{
					if(data[j] == '1')
						p++;
				}
					
				k++;
				if(k == step)
				{
					k = 0;
					flag = flag == 0 ? 1 : 0;
				}				
			}
			if( p % 2 != 0 )
				data[step-1] = '1';
		}
		data[dataLength] = '0';
		int count = 0;
		for(int i = 0; i < dataLength; i++) 
			data[dataLength] = data[dataLength] == data[i] ? '0' : '1';
		data[dataLength+1] = '\0';  
	}
	
	void acceptReceivedData() {
		cout << "Enter the received data : ";
		cin >> receivedData; 
	}

	void checkSum() {
		char checkParity = '0';
		for(int i = 0; i < dataLength; i++)
			checkParity = checkParity == receivedData[i] ? '0' : '1';			//checking parity changing checkparity to 0 or 1 alternately
		if (receivedData[dataLength] == checkParity)						// parity checking
			cout << "Data received successfully!" << endl;					
		else {
			cout << "Data error : " << endl;
			/*int i;
			for(i = 0; i < parityBit; i++) {
				int temporary = pow(2, i);
				char tempCheck = '0';
    	        for(int j = temporary+1; j <= dataLength; j++) {
        	        if(((j - temporary) / temporary) % 2 == 0 )
            	        tempCheck = tempCheck == receivedData[j-1] ? '0' : '1';
	       	    }
				error[i] = tempCheck == receivedData[temporary-1] ? '0' : '1';				
			}
			cout << endl;
			int lenError = i, j = lenError-1;
			while(j >= 0) {
				errorPosition <<= 1;
				errorPosition += error[j] == '1' ? 1 : 0;
				j--;
			}
			if(errorPosition != 0) {
				for(int k = parityBit-1; k >= 0; k--) 
					cout << error[k];
				cout << endl << "Error position at : " << errorPosition << endl;
			}
			else
				cout << "Error in parity bit!!" << endl;
			int err = (errorPosition != 0 ? errorPosition : dataLength);
			receivedData[err-1] = receivedData[err-1] == '1' ? '0' : '1';
			
			cout << "Received data must be : " << receivedData << endl; */		
			int step = 0, flag = 0, k = 0;
			int p = 0, errbit = 0; 
			int rDataLen = strlen(receivedData);
			for(int i = 0; i < parityBit; i++)
			{
				flag = 1;
				step = pow(2,i);
				p = 0;
				for(int j=step-1; j < rDataLen; j++)
				{
					if(flag == 1)
					{
						if(receivedData[j] == '1')
						p++;
					}
					
					k++;
					if(k == step)
					{
						k = 0;
						flag = flag == 0 ? 1 : 0;
					}				
				}
				if( p % 2 != 0 )
					error[i] = '1';
				else
					error[i] = '0';
			}
			for(int i = parityBit-1; i >= 0; i--)
				cout<<error[i];
			for(int i = parityBit-1; i >= 0; i--)
			{
				errbit += pow(2,i) * (int(error[i])-48);
			}
			cout << "\nError at position: " << errbit;
			receivedData[errbit-1] = receivedData[errbit-1] == '0' ? '1' : '0';
			cout << "\nReceived Data must be: " << receivedData;
		}
				
	}
		
	void display() {
		cout << data << endl;
	}
	
};

int main() {
	Hamming Object;
	Object.acceptData();
	Object.display();
	Object.calculateParity();
	cout << "Data sent is : ";
	Object.display();
	Object.acceptReceivedData();
	Object.checkSum();
	return 0;
}
