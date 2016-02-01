#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn=1100;
const int oo=0x3f3f3f3f;

struct Edge
{
    int v, cost, nxt;
} edge[maxn*maxn];

int n, m, pre[maxn], low[maxn], dfn, ans;
int head[maxn], e;

void init()
{
    memset(pre, 0, sizeof pre);
    memset(low, 0, sizeof low);
    memset(head, -1, sizeof head);
    e=dfn=0;
    ans=oo;
}

void AddEdge(int u, int v, int c)
{
    edge[e].v=v;
    edge[e].nxt=head[u];
    edge[e].cost=c;
    head[u]=e++;
}

void Tarjan(int u, int fa)
{
    pre[u]=low[u]=++dfn;
    for(int i=head[u]; ~i; i=edge[i].nxt)
    {
        if(i==(fa^1))continue ;
        int v=edge[i].v;
        if(!pre[v])
        {
            Tarjan(v, i);
            low[u]=min(low[u], low[v]);
            if(pre[u]<low[v])
                ans=min(ans, edge[i].cost);
        }
        else
            low[u]=min(low[u], pre[v]);
    }
}

int main()
{
    while(~scanf("%d%d", &n, &m) && n+m)
    {
        init();
        while(m--)
        {
            int u, v, c;
            scanf("%d%d%d", &u, &v, &c);
            AddEdge(u, v, c);
            AddEdge(v, u, c);
        }
        int cnt=0;
        for(int i=1; i<=n; i++)
            if(!pre[i])
            {
                cnt++;
                Tarjan(i, -1);
            }
        if(cnt>1)
            puts("0");
        else if(ans==oo)
            puts("-1");
        else if(ans==0)
            puts("1");
        else printf("%d\n", ans);
    }
    return 0;
}
