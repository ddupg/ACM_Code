#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <stack>
#include <queue>
using namespace std;
const int maxn=200000+100;

struct Edge
{
    int v, nxt;
} edge[3000010];

int n, m;
int pre[maxn], low[maxn], dfn, head[maxn], tot;
int belong[maxn], block, bridge;
stack<int> S;
bool ins[maxn];

void init()
{
    memset(head, -1, sizeof head);
    memset(pre, 0, sizeof pre);
    memset(low, 0, sizeof low);
    memset(ins, 0, sizeof ins);
    memset(belong, 0, sizeof belong);
    dfn=tot=block=bridge=0;
}

void AddEdge(int u, int v)
{
    edge[tot].v=v;
    edge[tot].nxt=head[u];
    head[u]=tot++;
}
void Tarjan(int u, int fa)
{
    pre[u]=low[u]=++dfn;
    S.push(u);
    ins[u]=true;
    for(int i=head[u]; ~i; i=edge[i].nxt)
    {
        if(i==(fa^1))continue ;
        int v=edge[i].v;
        if(!ins[v])
        {
            Tarjan(v, i);
            low[u]=min(low[u], low[v]);
            if(low[v]>pre[u])
                bridge++;
        }
        else low[u]=min(low[u], pre[v]);
    }
    if(low[u]==pre[u])
    {
        block++;
        while(true)
        {
            int x=S.top();
            S.pop();
            ins[x]=false;
            belong[x]=block;
            if(x==u)break;
        }
    }
}

vector<int> G[maxn];
int d[maxn];
bool vis[maxn];
queue<int> q;
int bfs(int s, int& ans)
{
    memset(d, 0, sizeof d);
    memset(vis, 0, sizeof vis);
    int t=s, head=0, tail=0;
    q.push(s);
    vis[s]=true;
    while(!q.empty())
    {
        int u=q.front();
        q.pop();
        for(int i=0; i<G[u].size(); i++)
        {
            int v=G[u][i];
            if(!vis[v])
            {
                vis[v]=true;
                d[v]=d[u]+1;
                if(d[v]>ans)
                    ans=d[t=v];
                q.push(v);
            }
        }
    }
    return t;
}

int main()
{
    while(~scanf("%d%d", &n, &m) && n+m)
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
        for(int i=0; i<=n; i++)
            G[i].clear();
        for(int u=1; u<=n; u++)
            for(int i=head[u]; ~i; i=edge[i].nxt)
            {
                int v=edge[i].v;
                if(belong[u]!=belong[v])
                    G[belong[u]].push_back(belong[v]);
            }
        int ans=0;
        int key=bfs(1, ans);
        bfs(key, ans);
        printf("%d\n", bridge-ans);
    }
    return 0;
}
