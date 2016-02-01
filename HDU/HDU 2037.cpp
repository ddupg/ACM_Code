#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;

struct Node
{
    int x, y;
    bool operator < (const Node a)const
    {
        return y<a.y || (y==a.y && x>a.y);
    }
}node[110];

int main()
{
    int n;
    while(cin>>n && n)
    {
        for(int i=0; i<n; i++)
            cin>>node[i].x>>node[i].y;
        sort(node, node+n);
        int ans=0, L=0;
        for(int i=0; i<n; i++)
            if(node[i].x>=L)
                ans++, L=node[i].y;
        cout<<ans<<endl;
    }
    return 0;
}
