#include <iostream>
#include <cstdio>
using namespace std;
const int maxn=30000+100;

int pre[maxn], n, m;

void init()
{
    for(int i=0; i<=n; i++)
        pre[i]=i;
}

int find(int x)
{
    return x==pre[x]?x:find(pre[x]);
}

void Union(int u, int v)
{
    u=find(u), v=find(v);
    if(u==v)return ;
    pre[v]=u;
}

int main()
{
    while(~scanf("%d%d", &n, &m) && n+m)
    {
        init();
        while(m--)
        {
            int t, x, y;
            scanf("%d", &t);
            if(t)scanf("%d", &x);
            for(int i=0; i<t-1; i++)
            {
                scanf("%d", &y);
                Union(x, y);
            }
        }
        int ans=0;
        for(int i=1; i<n; i++)
            ans+=(find(0)==find(i));
        printf("%d\n", ans+1);
    }
    return 0;
}
