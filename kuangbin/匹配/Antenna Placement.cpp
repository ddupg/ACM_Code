#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;
const int maxn=500;
int N;
vector<int> G[maxn];
int match[maxn];
bool inq[maxn], inp[maxn], inb[maxn];
int head, tail;
int Q[maxn];
int start, finish;
int NewBase;
int fa[maxn], base[maxn];
int Count;

void init()
{
    for(int i=0; i<maxn; i++)
        G[i].clear();
    N=0;
}

void Push(int u)
{
    Q[tail++]=u;
    inq[u]=true;
}
int Pop()
{
    int res=Q[head++];
    return res;
}
int FindCommonAncestor(int u, int v)
{
    memset(inp, 0, sizeof inp);
    while(true)
    {
        u=base[u];
        if(u==start)break;
        u=fa[match[v]];
    }
    while(true)
    {
        v=base[v];
        if(inp[v])break;
        v=fa[match[v]];
    }
    return v;
}
void ResetTrace(int u)
{
    int v;
    while(base[u]!=NewBase)
    {
        v=match[u];
        inb[base[u]]=inb[base[v]]=true;
        u=fa[v];
        if(base[u]!=NewBase)fa[u]=v;
    }
}
void BloosomContract(int u, int v)
{
    NewBase = FindCommonAncestor(u, v);
    memset(inb, 0, sizeof inb);
    ResetTrace(u);
    ResetTrace(v);
    if(base[u]!=NewBase)fa[u]=v;
    if(base[v]!=NewBase)fa[u]=u;
    for(int tu=1; tu<=N; tu++)
        if(inb[base[tu]])
        {
            base[tu]=NewBase;
            if(inq[tu])Push(tu);
        }
}
void FindAugmentingPath()
{
    memset(inq, 0, sizeof inq);
    memset(fa, 0, sizeof fa);
    for(int i=1; i<=N; i++)
        base[i]=i;
    head=tail=1;
    Push(start);
    finish=0;
    while(head<tail)
    {
        int u=Pop();
        for(int i=0; i<G[u].size(); i++)
        {
            int v=G[u][i];
            if(base[u]!=base[v] && match[u]!=v)
            {
                if(v==start || (match[v]>0 && fa[match[v]]>0))
                    BloosomContract(u, v);
                else if(fa[v]==0)
                {
                    fa[v]=u;
                    if(match[v]>0)
                        Push(match[v]);
                    else
                    {
                        finish=v;
                        return ;
                    }
                }
            }
        }
    }
}
void AugmentPath()
{
    int u, v, w;
    u=finish;
    while(u>0)
    {
        v=fa[u];
        w=match[v];
        match[v]=u;
        match[u]=v;
        u=w;
    }
}
void Edmonds()
{
    memset(match, 0, sizeof match);
    for(int u=1; u<=N; u++)
        if(match[u]==0)
        {
            start=u;
            FindAugmentingPath();
            if(finish>0)AugmentPath();
        }
}
int PrintMatch()
{
    Count=0;
    for(int u=1; u<=N; u++)
        if(match[u]>0)
            Count++;
    return (Count>>1);
}
const int dx[]={0, 0, -1, 1};
const int dy[]={1, -1, 0, 0};
bool inside(int x, int y, int n, int m)
{
    return x && y && x<=n && y<=m;
}
int main()
{
    int T, n, m;
    char g[55][55];
    int id[55][55];
    scanf("%d", &T);
    while(T--)
    {
        init();
        scanf("%d%d", &n, &m);
        for(int i=1; i<=n; i++)
        {
            scanf("%s", g[i]+1);
            for(int j=1; j<=m; j++)
                id[i][j]=++N;
        }
        int cnt=0;
        for(int i=1; i<=n; i++)
            for(int j=1; j<=m; j++)
                if(g[i][j]=='*')
                {
                    cnt++;
                    for(int k=0; k<4; k++)
                    {
                        int x=dx[k]+i, y=dy[k]+j;
                        if(inside(x, y, n, m) && g[x][y]=='*')
                            G[id[i][j]].push_back(id[x][y]);
                    }
                }
        Edmonds();
        printf("%d\n", cnt-PrintMatch());
    }
    return 0;
}
