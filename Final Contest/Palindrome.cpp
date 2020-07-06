#include<bits/stdc++.h>
using namespace std;

  
string solve(string str) 
{ 
    int n = str.size(); 
    bool DP[n][n];   
    memset(DP, 0, sizeof(DP)); 
    
    for (int i = 0; i < n; ++i) 
        DP[i][i] = true; 
  
    int mxlen = 1; 
    int start = 0; 
    for (int i = 0; i < n - 1; ++i) { 
        if (str[i] == str[i + 1]) { 
            DP[i][i + 1] = true; 
            start = i; 
            mxlen = 2; 
        } 
    } 
  
    for (int k = 3; k <= n; ++k) { 
        for (int i = 0; i < n - k + 1; ++i) { 
            int j = i + k - 1; 
  
            if (DP[i + 1][j - 1] && str[i] == str[j]) { 
                DP[i][j] = true; 
  
                if (k > mxlen) { 
                    start = i; 
                    mxlen = k; 
                } 
            } 
        } 
    } 
    return str.substr(start,mxlen); 
} 

int main()
{
    string s;
    cin>>s;
    cout<<solve(s)<<endl;
}