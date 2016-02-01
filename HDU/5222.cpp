#pragma comment(linker, "/STACK:102400000,102400000")
#include <iostream>
#include <cstring>
#include <cstdio>
using namespace std;
const int maxn=1000000+100;

struct Edge
{
    int v, nxt;
    Edge(int v=0, int nxt=0):v(v), nxt(nxt){}
} edge[maxn];

int tot, pre[maxn], head[maxn], c[maxn];

void init()
{
    tot=0;
    memset(pre, -1, sizeof pre);
    memset(head, -1, sizeof head);
}

void AddEdge(int u, int v)
{
    edge[tot]=Edge(v, head[u]);
    head[u]=tot++;
}

int find(int x)
{
    if(pre[x]==-1)return x;
    return pre[x]=find(pre[x]);
}

bool dfs(int u)
{
    c[u]=-1;
    for(int i=head[u]; ~i; i=edge[i].nxt)
    {
        int v=edge[i].v;
        if(c[v]<0)return false;
        else if(!c[v] && !dfs(v))return false;
    }
    c[u]=1;
    return true;
}

bool toposort(int n)
{
    memset(c, 0, sizeof c);
    for(int i=1; i<=n; i++)if(!c[find(i)])
        if(!dfs(find(i)))return false;
    return true;
}

int main()
{
    int T;
    scanf("%d", &T);
    while(T--)
    {
        init();
        int n, m1, m2, u, v;
        scanf("%d%d%d", &n, &m1, &m2);
        bool ans=0;
        while(m1--)
        {
            scanf("%d%d", &u, &v);
            u=find(u), v=find(v);
            if(u==v)
                ans=true;
            else pre[u]=v;
        }
        while(m2--)
        {
            scanf("%d%d", &u, &v);
            AddEdge(find(u), find(v));
        }
        if(ans || !toposort(n))
            puts("YES");
        else puts("NO");
    }
    return 0;
}
