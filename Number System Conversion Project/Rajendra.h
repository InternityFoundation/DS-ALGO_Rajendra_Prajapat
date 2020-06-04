#include<iostream>
#include<algorithm>
#include<stack>
#include<math.h>
#include<string>
using namespace std;

//for single digit preprocess
char singleDigitPreprocees(int n)
{
    if(n<10) return n+'0';
    else if(n >= 10){
        return 'A'+(n-10);
    } 
}

//from any base to decimal
int toDecimal(string number,int base /*= 16*/)
{
    int ans = 0;
    int size = number.length();

    for(int i=0;i<size;i++)
    {
        if(number[i]>='A')
        {
            ans += (number[i]-'A'+10) *pow(base,size-i-1);
        } 
        else
        {
            ans += (number[i]-'0') *pow(base,size-i-1);
        }
    }
    return ans;
}

//Decimal to any base
string decimalTo(int decimal,int base = 16)
{
    stack<char> remainders;
    if(decimal == 0) return "0";
    while(decimal > 0)
    {
        char rem = singleDigitPreprocees(decimal%base);
        decimal = decimal/base;
        remainders.push(rem);
    }

    string ans = ""; 
    while(!remainders.empty())
    {
        ans += remainders.top();
        remainders.pop();
    }
    return ans;
}

// Binary to Octal conversion
string binaryToOctal(string binary)
{
    int size = binary.length();
    int index = size-1;
    
    stack<char> oct;
 
    while(index >= 0)
    {
        string substring;
        if(index-0 < 3)
        {
            substring = binary.substr(0,index+1);
        }
        else 
        {
            substring = binary.substr(index-2,3);
        }

        index-=3;
        int dec = toDecimal(substring,2);
        oct.push(dec+'0');
    }

    string octal = ""; 
    while(!oct.empty())
    {
        octal += oct.top();
        oct.pop();
    }
    return octal;
}

//Octal to Binary conversion
string octalToBinary(string octal)
{
    int size = octal.length();
    string binary="";
    for(int i=0;i<size;i++)
    {
        string x= "";//decimalTo(octal[i]-'0',2);
        if(x.length()<3)
        {
            if(x.length()==1)
                x = "00"+x;
            else{
                x = "0"+x;
            }
        }
        binary += x;
    }
    return binary;
}
