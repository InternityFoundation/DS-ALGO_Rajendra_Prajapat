#include<bits/stdc++.h>
using namespace std;

// typedef struct treeNode{
//     int val;
//     struct treeNode *left;
//     struct treeNode *right;
//     struct treeNode *parent;
// }treeNode;

int main()
{
    int nodes,edges;
    
    //input number of nodes and number of edges    
    cin>> nodes>>edges;
    vector<int> tree[nodes];
    int parents[nodes];
    //root is always 0
    parents[0]=-1;  
    for(int i=0;i<edges;i++)
    {
        int a,b;
        cin>>a>>b;
        tree[a].push_back(b); // one way as we are working with trees
        parents[b]=a;
    }
    
    //number of queries 
    int Q;
    cin>>Q;
    while (Q--)
    {
        int p,q;
        cin>>p>>q;

        vector<int> vc1;
        vector<int> vc2;
        
        while(parents[p]!=-1)
        {
            vc1.push_back(p);
            p = parents[p];
        }
        
        while(parents[q]!=-1)
        {
            vc2.push_back(q);
            q = parents[q];
        }
        
        reverse(vc1.begin(),vc1.end());
        reverse(vc2.begin(),vc2.end());

        int i=0;
        int LCA=0;//root
        while (i<vc1.size() and i<vc2.size())
        {
            if(vc1[i]==vc2[i])
            {
                LCA = vc1[i];
            }
            else break;
            i++;
        }
        cout<<"LCA : "<<LCA<<endl;
    }
    
    return 0;
}

/* Sample INPUT
7 6
0 1
0 2
1 3
1 4
2 5
2 6

2
3 4
1 6
*/

/*
                  0
            1           2
        3      4    5       6
     
*/

/*Sample Output
1
0    
*/


