#include<bits/stdc++.h>
using namespace std;

int main()
{
    int nodes,edges;
    
    //input number of nodes and number of edges    
    cin>> nodes>>edges;
    vector<int> tree[nodes];
    vector<int> val(nodes);
    int parents[nodes];

    //input values to each nodes
    for(int i=0;i<nodes;i++)
    {
        cin>>val[i];
    }

    //root is always 0
    parents[0]=-1;  

    for(int i=0;i<edges;i++)
    {
        int a,b;
        cin>>a>>b;
        tree[a].push_back(b); // one way as we are working with trees
        parents[b]=a;
    }

    int ans = 0;
    for(int i=0;i<nodes;i++)
    {
        int p = i;
        bool flag = 1;
        while(parents[p]!=-1)
        {
            p = parents[p];
            if(val[p]>val[i])
            {
                flag = 0;
                break;
            }
        }

        if(flag){
            ans++; //reached to root
            cout<<"node with value: "<<i<<" : "<<val[i]<<endl;
        } 
    }        
    cout<<ans<<endl;
    return 0;

}

/* Sample INPUT:1
6 5
3 1 4 3 1 5
0 1
0 2
1 3
2 4
2 5

*/

/*
                  0(3)
            1(1)           2(4)
        3(3)          4(1)       5(5)
     
*/

/*Sample Output:2

node with value: 0 : 3
node with value: 2 : 4
node with value: 3 : 3
node with value: 5 : 5
4
*/

/*
Input:2
4 3
3 3 4 2
0 1
1 2
1 3

Output: 2
node with value: 0 : 3
node with value: 1 : 3
node with value: 2 : 4
3
*/