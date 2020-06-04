#include<string>
using namespace std;
class check{
	public:
		static bool binary(string binary){
			int len = binary.length();
			if(len > 64) return 0;
			for(int i = 0 ; i < len ;i++)
				if(!(binary[i] == '0'||binary[i] == '1'))
					return 0;
			return 1;			
		}		
		static bool decimal(string decimal){
			int len = decimal.length();
			if(len > 18 )return 0;
			for(int i = 0 ; i < len ; i++)
				if(!(decimal[i] >= '0' && decimal[i] <= '9'))
					return 0;
				
			return 1;
		}		
		static bool hexadecimal(string hexadecimal){
			int len = hexadecimal.length();
			if(len > 12) return 0;
			for(int i = 0 ; i < len ; i++)
				if(!(hexadecimal[i] >= '0' && hexadecimal[i] <= '9') && !(hexadecimal[i] >= 'A' && hexadecimal[i] <= 'F'))
					return 0;
			return 1;
		}	
		static bool octal(string octal){
			int len = octal.length();
			if(len > 21) return 0;
			for(int i = 0 ; i < len ; i++)
				if(!(octal[i] >='0' && octal[i] <='7'))
					return 0;
			return 1;
		}			
};
