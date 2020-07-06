#include<bits/stdc++.h>
using namespace std;

int main()
{
    stack<int> s; 
    s.push(-1); 
    int ans = 0; 

    string str;
    cin>>str;
    
    //Using stack implementation 
    int n = str.length(); 
    
    for (int i=0; i<n; i++) 
    { 
        if (str[i] == '(') 
          s.push(i);   
        else 
        { 
            s.pop(); 
            if (!s.empty()) 
                ans = max(ans, i - s.top()); 
            else s.push(i); 
        } 
    }
    cout<<ans<<endl;
}