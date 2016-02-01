#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;
const int maxn=50;
int n, G[maxn][maxn];
int link[maxn];
bool inq[maxn], inp[maxn], inb[maxn];
int head, tail;
int Q[maxn];
int start, finish;
int NewBase, fa[maxn], base[maxn];

void Push(int u)
{
    Q[tail++]=u;
    inq[u]=true;
}
int Pop()
{
    int ans=Q[head++];
    return ans;
}
int FindCommonAncestor(int u, int v)
{
    memset(inp, 0, sizeof inp);
    while(true)
    {
        u=base[u];
        inp[u]=true;
        if(u==start)break;
        u=fa[link[u]];
    }
    while(true)
    {
        v=base[v];
        if(inp[v])break;
        v=fa[link[v]];
    }
    return v;
}
void ResetTrace(int u)
{
    int v;
    while(base[u]!=NewBase)
    {
        v=link[u];
        inb[base[u]]=inb[base[v]]=true;
        u=fa[v];
        if(base[u]!=NewBase)fa[u]=v;
    }
}
void BollsomContract(int u, int v)
{
    NewBase=FindCommonAncestor(u, v);
    memset(inb, 0, sizeof inb);
    ResetTrace(u);
    ResetTrace(v);
    if(base[u]!=NewBase)fa[u]=v;
    if(base[v]!=NewBase)fa[v]=u;
    for(int tu=1; tu<=n; tu++)
        if(inb[base[tu]])
        {
            base[tu]=NewBase;
            if(!inq[tu])Push(tu);
        }
}
void FindAugmentingPath()
{
    memset(inq, 0, sizeof inq);
    memset(fa, 0, sizeof fa);
    for(int i=1; i<=n; i++)
        base[i]=i;
    head=tail=1;
    Push(start);
    finish=0;
    while(head<tail)
    {
        int u=Pop();
        for(int v=1; v<=n; v++)
        {
            if(G[u][v] && base[u]!=base[v] && link[u]!=v)
            {
                if(v==start || (link[v]>0 && fa[link[v]]>0))
                    BollsomContract(u, v);
                else if(fa[v]==0)
                {
                    fa[v]=u;
                    if(link[v]>0)
                        Push(link[v]);
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
        w=link[v];
        link[v]=u;
        link[u]=v;
        u=w;
    }
}
void Edmonds()
{
    memset(link, 0, sizeof link);
    for(int u=1; u<=n; u++)
    {
        if(link[u]==0)
        {
            start=u;
            FindAugmentingPath();
            if(finish>0)AugmentPath();
        }
    }
}
int PrintMatch()
{
    int cnt=0;
    for(int u=1; u<=n; u++)
        if(link[u]>0)
            cnt++;
    return cnt>>1;
}
struct Edge
{
    int u, v;
} edge[maxn*maxn];

int main()
{
    int u, v, m;
    while(~scanf("%d%d", &n, &m))
    {
        int g[maxn][maxn]={0};
        memset(G, 0, sizeof G);
        for(int i=0; i<m; i++)
        {
            scanf("%d%d", &u, &v);
            edge[i].u=u, edge[i].v=v;
            g[u][v]=g[v][u]=G[u][v]=G[v][u]=1;
        }
        Edmonds();
        int cnt=PrintMatch();
        vector<int> ans;
        ans.clear();
        for(int i=0; i<m; i++)
        {
            memcpy(G, g, sizeof g);
            for(int j=1; j<=n; j++)
                G[edge[i].u][j]=G[edge[i].v][j]=G[j][edge[i].u]=G[j][edge[i].v]=0;
            Edmonds();
            if(cnt-1>PrintMatch())
                ans.push_back(i);
        }
        printf("%d\n", ans.size());
        for(int i=0; i<ans.size(); i++)
        {
            if(i)putchar(' ');
            printf("%d", ans[i]+1);
        }
        puts("");
    }
    return 0;
}
