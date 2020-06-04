#include <iostream>
#include<string>
#include<vector>
#include<sstream>
#include<limits>
#include "Check.h"
#include "Abhishek.h"
#include "Rajendra.h"
#include "Aditya.h"
using namespace std; 
//--------------------------------------------
void binarytodecimal ( string binary );
void decimaltobinary ( long long decimal );
void octaltodecimal ( long long octal );
void decimaltooctal ( long long decimal );
//--------------------------------------------
char singleDigitPreprocees(int n);
string decimalTo(int decimal,int base /*= 16*/);
int toDecimal(string number,int base /*= 16*/);
string binaryToOctal(string binary);
string octalToBinary(string octal);
//--------------------------------------------
void binarytoHex(int n);
void hex2binary(string hex);
void octaltohex(int n);
void hex2octal(string hex);
//--------------------------------------------

int display_menu(){
	system("cls");
	cout<<"\n\n\t\t\t NUMBER CONVERSION SYSTEM\n\n";
	cout<<"\t\t===========================================\n\n";	           
	cout<<"\t\t\t1. Binary to Decimal\n\n\t\t\t2. Decimal to Binary\n\n\t\t\t3. Octal to Decimal\n\n\t\t\t4. Decimal to Octal\n\n";
	cout<<"\t\t\t5. Decimal to Hexadecimal\n\n\t\t\t6. Hexadecimal to Decimal\n\n\t\t\t7. Binary to Octal\n\n\t\t\t8. Octal to Binary\n\n";
	cout<<"\t\t\t9. Binary to Hexadecimal\n\n\t\t\t10. Hexadecimal to Binary\n\n\t\t\t11. Octal to Hexadecimal\n\n\t\t\t12. Hexadecimal to Octal\n\n";
	cout<<"\t\t\t13. Exit\n\n";
	cout<<"    SELECT OPTION : \t";
}



inline void input_prompt(string original,string modified){
	cout << "\n\n\t\t"<< original << " to " << modified << " Conversion\n\n";
	cout << "\tEnter " << original <<" number to convert it into its " << modified << " equivalent:\n\t";
}

inline void output_prompt(string res){
	cout << "\n\tEquivalent "<< res <<" number : ";
}

inline void error(){
	cout << "\n\tIncorrect input format !";
	//cin.clear(); 
	//cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');	
}

inline void pause(){
	cout<<"\n\tPress Enter to continue...";
	getchar();	
}

int main(){
	system("MODE CON COLS=80 LINES=45");
	int option;
	do{		
		display_menu();
		cin >> option;
		while(cin.fail()){
			cout<<"\n\tIncorrect option !";
			cin.clear(); 
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');			
			cout << "Press Enter to continue...";
			getchar();
			display_menu();
			cin >> option;

		}
		switch(option){
			case 1 : {
				system("cls");
				string binary;				
				input_prompt("Binary","Decimal");
				cin.ignore();
				getline(cin, binary);
				if(!check::binary(binary))
					error();				
				else{
					output_prompt("Decimal");
					binarytodecimal(binary);					
				}
				pause();
				break;
			}
			case 2 : {
				system("cls");
				string decimal;				
				input_prompt("Decimal","Binary");
				cin.ignore();
				getline(cin, decimal);
				if( cin.fail()||!check::binary(decimal))
					error();				
				else{
					output_prompt("Binary");
					int decimalNum;
					istringstream iss(decimal);
					iss>>decimalNum;
					decimaltobinary(decimalNum);
				}
				pause();
				break;
			}
			case 3 : {
				system("cls");
				string octal;				
				input_prompt("Octal","Decimal");
				cin.ignore();
				getline(cin, octal);
				if(cin.fail()||!check::octal(octal))
					error();									
				else{
					output_prompt("Decimal");
					long long octalNum;
					istringstream iss(octal);
					iss >> octalNum;
					octaltodecimal(octalNum);					
				}
				pause();
				break;
			}
			case 4 : {
				system("cls");
				string decimal;				
				input_prompt("Decimal","Octal");
				cin.ignore();
				getline(cin, decimal);
				if(cin.fail()||!check::decimal(decimal))
					error();				
				else{
					output_prompt("Octal");
					long long decimalNum;
					istringstream iss(decimal);
					iss >> decimalNum;
					decimaltooctal(decimalNum);					
				}
				pause();
				break;
			}
			case 5 : {
				system("cls");
				string decimal;				
				input_prompt("Decimal","Hexadecimal");
				cin.ignore();
				getline(cin, decimal);
				if(cin.fail()||!check::decimal(decimal))
					error();				
				else{
					output_prompt("Hexadecimal");
					int decimalNum;
					istringstream iss(decimal);
					iss >> decimalNum;					
					cout << decimalTo(decimalNum,16);					
				}
				pause();
				break;
			}
			case 6 : {
				system("cls");
				string hexadecimal;				
				input_prompt("Hexadecimal","Decimal");
				cin.ignore();
				getline(cin, hexadecimal);
				if(!check::hexadecimal(hexadecimal))
					error();				
				else{
					output_prompt("Hexadecimal");
					cout << toDecimal(hexadecimal,16);					

				}
				pause();
				break;
			}		
			case 7 : {
				system("cls");
				string binary;				
				input_prompt("Binary","Octal");
				cin.ignore();
				getline(cin, binary);
				if(!check::binary(binary))
					error();				
				else{
					output_prompt("Octal");
					cout << binaryToOctal(binary);
				}
				pause();
				break;
			}			
			case 8 : {
				system("cls");
				string octal;				
				input_prompt("Octal","Binary");
				cin.ignore();
				getline(cin, octal);
				if(cin.fail()||!check::octal(octal))
					error();									
				else{
					output_prompt("Binary");
					cout << octalToBinary(octal);				
				}
				pause();
				break;
			}	
			case 9 : {
				system("cls");
				string binary;				
				input_prompt("Binary","Hexadecimal");
				cin.ignore();
				getline(cin, binary);
				if(!check::binary(binary))
					error();				
				else{
					output_prompt("Hexadecimal");
					istringstream iss(binary);
					int binaryNum;
					iss >> binaryNum ;
					binarytoHex(binaryNum);
				}
				pause();
				break;
			}		
			case 10 : {
				system("cls");
				string hexadecimal;				
				input_prompt("Hexadecimal","Binary");
				cin.ignore();
				getline(cin, hexadecimal);
				if(!check::hexadecimal(hexadecimal))
					error();									
				else{
					output_prompt("Binary");
					hex2binary(hexadecimal);
				}
				pause();
				break;
			}		
			case 11 : {
				system("cls");
				string octal;				
				input_prompt("Octal","Hexadecimal");
				cin.ignore();
				getline(cin, octal);
				if(cin.fail()||!check::octal(octal))
					error();									
				else{
					output_prompt("Hexadecimal");
					int octalNum;
					istringstream iss(octal);
					iss >> octalNum;
					octaltohex(octalNum);					
				}
				pause();
				break;
			}	
			case 12 : {
				system("cls");
				string hexadecimal;				
				input_prompt("Hexadecimal","Octal");
				cin.ignore();
				getline(cin, hexadecimal);
				if(!check::hexadecimal(hexadecimal))
					error();									
				else{
					output_prompt("Octal");
					hex2octal(hexadecimal);
				}
				pause();
				break;
			}										
			default :
				cout<<"\n\tBye !  :)";		
				break;					
		}
	}while(option != 13);
}

