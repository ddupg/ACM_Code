#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <stack>
using namespace std;
const int maxn=5500;

struct Edge
{
    int v, nxt;
} edge[20000+100];

int n, m, e, dfn, pre[maxn], low[maxn], head[maxn], belong[maxn], scc, du[maxn];
bool ins[maxn];
stack<int> s;

void init()
{
    memset(head, -1, sizeof head);
    memset(pre, 0, sizeof pre);
    memset(du, 0, sizeof du);
    memset(belong, 0, sizeof belong);
    memset(ins, 0, sizeof ins);
    dfn=e=scc=0;
}

void AddEdge(int u, int v)
{
    edge[e].v=v;
    edge[e].nxt=head[u];
    head[u]=e++;
}

void Tarjan(int u, int fa)
{
    pre[u]=low[u]=++dfn;
    s.push(u);
    ins[u]=true;
    for(int i=head[u]; ~i; i=edge[i].nxt)
    {
        if(i==(fa^1))continue ;
        int v=edge[i].v;
        if(!pre[v])
        {
            Tarjan(v, i);
            low[u]=min(low[u], low[v]);
        }
        else if(ins[v]) low[u]=min(low[u], pre[v]);
    }
    if(low[u]==pre[u])
    {
        scc++;
        while(true)
        {
            int x=s.top();
            s.pop();
            ins[x]=false;
            belong[x]=scc;
            if(x==u)break;
        }
    }
}

int main()
{
    while(~scanf("%d%d", &n, &m))
    {
        init();
        while(m--)
        {
            int u, v;
            scanf("%d%d", &u, &v);
            AddEdge(u, v);
            AddEdge(v, u);
        }
        for(int i=1; i<=n; i++)
            if(!pre[i])
                Tarjan(i, -1);
        for(int i=1; i<=n; i++)
            for(int j=head[i]; ~j; j=edge[j].nxt)
                if(belong[i]!=belong[edge[j].v])
                    du[belong[i]]++;
        int sum=0;
        for(int i=1; i<=scc; i++)
            sum+=(du[i]==1);
        printf("%d\n", (sum+1)>>1);
    }
    return 0;
}
