#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;
const int maxn=250;
int n;
int link[maxn];
bool inq[maxn], inp[maxn], inb[maxn];
int head, tail;
int Q[maxn];
int start, finish;
int NewBase, fa[maxn], base[maxn];
vector<int> G[maxn];
void CreateGraph()
{
    int u, v;
    scanf("%d", &n);
    while(~scanf("%d%d", &u, &v))
    {
        G[u].push_back(v);
        G[v].push_back(u);
    }
}
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
        for(int i=0; i<G[u].size(); i++)
        {
            int v=G[u][i];
            if(base[u]!=base[v] && link[u]!=v)
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
        if(link[u]==0)
        {
            start=u;
            FindAugmentingPath();
            if(finish>0)AugmentPath();
        }
}
void PrintMatch()
{
    int cnt=0;
    for(int u=1; u<=n; u++)
        if(link[u]>0)
            cnt++;
    printf("%d\n", cnt);
    for(int u=1; u<=n; u++)
        if(u<link[u])
            printf("%d %d\n", u, link[u]);
}
int main()
{
    CreateGraph();
    Edmonds();
    PrintMatch();
    return 0;
}
