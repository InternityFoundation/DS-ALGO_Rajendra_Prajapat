#include<bits/stdc++.h>
using namespace std;

int main()
{
    int nodes,edges;

    //input number of nodes and number of edges    
    cin>> nodes>>edges;
    vector<int> tree[nodes];
    vector<int> val(nodes);
    
    //input weigts of each node
    for(int i=0;i<nodes;i++)
    {
        cin>>val[i];
    }
     
    for(int i=0;i<edges;i++)
    {
        int a,b;
        cin>>a>>b;
        tree[a].push_back(b); // one way as we are working with trees
    }

    vector<int> ans(2000,INT_MIN); //max 2000 levels
    
    //implement BFS to track each level
    queue<int> qu;
    bool visited[nodes];
    int level[2000];
    qu.push(0);
    visited[0]=1;
    level[0]=0;
    ans[0] = val[0];
    int highest_level = 0;
    
    while (!qu.empty())
    {
        int current = qu.front();
        qu.pop();
        //traverse all the childs
        for(int i:tree[current])
        {
            if(!visited[i])
            {
                qu.push(i);
                level[i]=level[current]+1;
                if(val[i]>ans[level[i]])
                {
                    ans[level[i]] = val[i];
                }
                highest_level = (level[i]>highest_level)?level[i]:highest_level;
            }
        }
    }
    for(int i=0;i<=highest_level;i++)
    {
        cout<<ans[i]<<" ";
    }
    cout<<endl;
    
    return 0;
}

/* Sample INPUT
7 6
5 6 10 8 12 5 9
0 1
0 2
1 3
1 4
2 5
2 6
5 10 12
*/
/*
                  5
            6           10
        8      12    5       9 
*/
/*Sample Output
5 10 12    
*/
