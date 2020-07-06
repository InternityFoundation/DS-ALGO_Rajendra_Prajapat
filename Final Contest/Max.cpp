#include<bits/stdc++.h>
using namespace std;

int cmp(string x, string y) 
{ 
    string a = x.append(y); 
    string b = y.append(x); 
    return a.compare(b) > 0 ? 1: 0; 
} 
 
int main()
{
    int n;  
    cin>>n;
    vector<string> vc(n);
    for(int i=0;i<n;i++)
    {
        cin>>vc[i];
    }

    sort(vc.begin(), vc.end(),cmp); 
    for (int i=0; i < vc.size() ; i++ ) 
        cout << vc[i]; 
}