//using DP
#include<bits/stdc++.h>
using namespace std;
int main()
{
    int n;
    cin>>n;

    //solution 

    int dp[n+1]={0};
    dp[1]=1;
    dp[2]=2;
    dp[3]=3;
    dp[4]=4;
    
    for(int i=1;i<=n;i++)
    {
         dp[i]=i;
         for(int k=1;k*k<=n;k++)
         {
             if(k*k>i)
             {
                 //done = 1;
                 break;
             }
             else 
            {
                dp[i]=min(dp[i],1+dp[i-k*k]);
            }
         }
    }
    cout<<dp[n]<<endl;
}