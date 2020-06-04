#include <iostream>
#include <string>
#include <cmath>
using namespace std;

//Binary to Hexadecimal
void binarytoHex(int n){
    int s=0;
    int i=1;
    int j=0;
    char hexanum[100];
    while(n>0){
        int r=n%10;
        s=s+r*i;
        n/=10;
        i*=2;
    }
  
    while(s>0){
        int r1=s%16;
        if(r1<10){
            hexanum[j]=r1+48;
            j++;
        }
        else{
            hexanum[j]=r1+55;
            j++;
        }
        s/=16;

    }
    for(int k=j-1; k>=0; k--) 
        cout << hexanum[k];

}

//Hexadecimal to Binary
void hex2binary(string hex){
    int result = 0;
    for (int i=0; i<hex.length(); i++) {
        if (hex[i]>=48 && hex[i]<=57)
        {
            result += (hex[i]-48)*pow(16,hex.length()-i-1);
        } else if (hex[i]>=65 && hex[i]<=70) {
            result += (hex[i]-55)*pow(16,hex.length( )-i-1);
        }
    }
    int binary[32];
    int i = 0; 
    while (result > 0) { 
        binary[i] = result % 2; 
        result/= 2; 
        i++; 
    } 
    for (int j = i - 1; j >= 0; j--) 
        cout << binary[j];

}

//Octal to Hexadecimal
void octaltohex(int n){
    int s=0;
    int i=1;
    int j=0;
    char hexanum[100];
    while(n>0){
        int r=n%10;
        s=s+r*i;
        n/=10;
        i*=8;
    }
  
    while(s>0){
        int r1=s%16;
        if(r1<10){
            hexanum[j]=r1+48;
            j++;
        }
        else{
            hexanum[j]=r1+55;
            j++;
        }
        s/=16;

    }
    for(int k=j-1; k>=0; k--) 
        cout << hexanum[k];
}

//Hexadecimal to Octal
void hex2octal(string hex){
    int result = 0;
    for (int i=0; i<hex.length(); i++) {
        if (hex[i]>=48 && hex[i]<=57)
        {
            result += (hex[i]-48)*pow(16,hex.length()-i-1);
        } else if (hex[i]>=65 && hex[i]<=70) {
            result += (hex[i]-55)*pow(16,hex.length( )-i-1);
        }
    }
    int octal[32];
    int i = 0; 
    while (result > 0) { 
        octal[i] = result % 8; 
        result/= 8; 
        i++; 
    } 
    for (int j = i - 1; j >= 0; j--) 
        cout << octal[j];

}
