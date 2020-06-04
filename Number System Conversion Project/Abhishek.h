#include<iostream>
#include<string>
#include<vector>
using namespace std;
void binarytodecimal( string binary ){
	
	// initialising decimal to 0 and setting the starting base value
	long long decimal = 0, base_val = 1, len = binary.length() ;
	 
	for (int i = len - 1; i >= 0; i--,base_val*=2)	// moving from LSB to MSB and doubling base value for each bit
		if(binary[i]=='1')
			decimal += base_val;					// add current base value to decimal if bit is set

	cout << decimal << "\n" ;						
		
}


void decimaltobinary( long long decimal ){
	
	// vector-binary will store the bits of decimal, 64 enought to store upto LLONG_MAX
	vector<bool> binary (64) ;
	int idx=0;

	while (decimal > 0){			
		
		binary[idx] = decimal & 1;	// finding the bit at idx'th index by dividing decimal and storing remainder
		decimal >>= 1;				// dividing decimal by 2 every time
		idx++;
		
	}
	idx--;
	while(idx >= 0)					// This loop prints the final binary number	
		cout << binary[idx--] ;
	cout << "\n";

}


void octaltodecimal( long long octal ){
	
	// initialising decimal to zero and starting base value to 1
	long long decimal = 0, base_val = 1 ;

	while(octal){								
		
		decimal += ( octal % 10 ) * base_val;	// taking the last digit of octal and adding to decimal by multiplying it by current base value
		octal /= 10	;							// dividing octal by 10 to get next digit in next iteration
		base_val *= 8;							// base value increases by 8 times as we move from LSB to MSB
		
	}

	cout << decimal << "\n";					
	
}


void decimaltooctal( long long decimal ){
	
	// vector-binary will store the bits of decimal, 22 enough to store upto LLONG_MAX
	vector<int> octal (22);
	int idx = 0;

	while(decimal){								// looping till decimal is greater than 0
		
		octal[idx] = decimal % 8;				// storing remainder after dividing current decimal value by 8
		decimal >>= 3;							// equivalent to dividing the decimal by 8
		idx++;
		
	}
	idx--;
	while(idx >= 0)								
		cout << octal[idx--] ;
	cout << "\n"; 
	
}
