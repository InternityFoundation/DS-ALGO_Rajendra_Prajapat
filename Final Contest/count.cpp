#include <bits/stdc++.h> 
using namespace std; 

   
int main() 
{ 
    int n;
    cin>>n;
    vector<int> vc(n);
    for(int i=0;i<n;i++)
    {
        cin>>vc[i];
    }

    int ans[n];
    for(int i = 0; i < n; i++) 
        ans[i] = 0; 

    for (int i = 0; i < n; i++) 
    { 
        for(int j = i+1; j < n; j++) 
        { 
            if (vc[j] < vc[i]) 
            {
                ans[i]++;
            }             
        } 
    }  

    for(int i = 0; i < n; i++) 
    {
        cout << ans[i] << " ";
    } 
    return 0; 
} 