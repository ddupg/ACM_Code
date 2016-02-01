#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

struct Node
{
    int p, id;
    bool operator < (const Node a)const
    {
        return p>a.p || (p==a.p && id<a.id);
    }
}node[10010];
bool vis[10010];

int find(int pos)
{
    for(int i=pos; i>=0; i--)
        if(!vis[i])return i;
}

int main()
{
    int n;
    while(~scanf("%d", &n))
    {
        memset(vis, 0, sizeof(vis));
        for(int i=0; i<n; i++)
            scanf("%d%d", &node[i].p, &node[i].id);
        sort(node, node+n);
        int ans=0;
        for(int i=0; i<n; i++)
        {
            int pos=find(node[i].id);
            if(!pos)continue ;
            ans+=node[i].p;
            vis[pos]=true;
        }
        printf("%d\n", ans);
    }
    return 0;
}
