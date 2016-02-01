#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <queue>
#include <vector>
#define clr(a, x) memset(a, x, sizeof a)
using namespace std;

const int maxn=100000+100;
const int DEG=30;

struct Edge
{
    int v, nxt;
} edge[maxn<<1];

int n, head[maxn], tot, fa[maxn][DEG], deg[maxn], sz[maxn];

void init()
{
    clr(head, -1);
    tot=0;
}

void AddEdge(int u, int v)
{
    edge[tot].v=v;
    edge[tot].nxt=head[u];
    head[u]=tot++;
}

void dfs(int u)
{
    for(int i=1; i<DEG; i++)
        fa[u][i]=fa[fa[u][i-1]][i-1];
    sz[u]=1;
    for(int i=head[u]; ~i; i=edge[i].nxt)
    {
        int v=edge[i].v;
        if(v==fa[u][0])continue ;
        deg[v]=deg[u]+1;
        fa[v][0]=u;
        dfs(v);
        sz[u]+=sz[v];
    }
}

int par(int u, int det)
{
    for(int i=0; det; det>>=1, i++)
        if(det&1)
            u=fa[u][i];
    return u;
}

int LCA(int u, int v)
{
    if(deg[u]>deg[v])swap(u, v);
    int tu=u, tv=v;
    tv=par(v, deg[v]-deg[u]);
    if(tu==tv)return tu;
    for(int i=DEG-1; i>=0; i--)
    {
        if(fa[tu][i]==fa[tv][i])continue ;
        tu=fa[tu][i], tv=fa[tv][i];
    }
    return fa[tu][0];
}

int main()
{
    scanf("%d", &n);
    init();
    for(int i=0; i<n-1; i++)
    {
        int u, v;
        scanf("%d%d", &u, &v);
        AddEdge(u, v);
        AddEdge(v, u);
    }
    deg[1]=0;
    fa[1][0]=1;
    dfs(1);
    int q;
    scanf("%d", &q);
    while(q--)
    {
        int u, v;
        scanf("%d%d", &u, &v);
        if(u==v)
        {
            printf("%d\n", n);
            continue ;
        }
        int lca=LCA(u, v);
        int len=deg[u]+deg[v]-2*deg[lca];
        if(len&1)
        {
            puts("0");
            continue ;
        }
        len>>=1;
        if(deg[u]==deg[v])
        {
            int tu=par(u, len-1), tv=par(v, len-1);
            printf("%d\n", n-sz[tu]-sz[tv]);
            continue ;
        }
        if(deg[u]<deg[v])swap(u, v);
        int tu=par(u, len-1);
        printf("%d\n", sz[fa[tu][0]]-sz[tu]);
    }
    return 0;
}
