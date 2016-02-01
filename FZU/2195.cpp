#include <iostream>
#include <cstdio>
#include <cstring>
#define clr(a, x) memset(a, x, sizeof a)
using namespace std;
typedef long long LL;
const int maxn=100000+100;

struct Edge
{
    int u, v, w, nxt;
    Edge(int u=0, int v=0, int w=0, int n=0):u(u), v(v), w(w), nxt(n) {}
} edge[maxn<<1];
int n, tot, head[maxn];
LL sz[maxn], ans;

void init()
{
    clr(head, -1);
    tot=0;
    clr(sz, 0);
    ans=0;
}

void AddEdge(int u, int v, int w)
{
    edge[tot]=Edge(u, v, w, head[u]);
    head[u]=tot++;
}

void dfs(int u)
{
    for(int i=head[u]; ~i; i=edge[i].nxt)
    {
        int v=edge[i].v;
        dfs(v);
        sz[u]+=sz[v]+edge[i].w;
    }
}

LL dp(int u)
{
    LL ans=sz[u];
    for(int i=head[u]; ~i; i=edge[i].nxt)
    {
        int v=edge[i].v;
        ans=min(ans, dp(v)+sz[u]-sz[v]-edge[i].w);
    }
    return ans;
}

int main()
{
    while(~scanf("%d", &n))
    {
        init();
        for(int i=0; i<n-1; i++)
        {
            int u, v, w;
            scanf("%d%d%d", &u, &v, &w);
            AddEdge(u, v, w);
        }
        dfs(1);
        printf("%I64d\n", dp(1));
    }
    return 0;
}
