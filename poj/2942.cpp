#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <stack>
using namespace std;
const int maxn=1100;

struct Edge
{
    int v, nxt;
    Edge(int v=0, int nxt=0):v(v), nxt(nxt) {}
} edge[maxn*maxn];

int n, m, head[maxn], tot;
int pre[maxn], low[maxn], dfn;
int block, bel[maxn];
bool ins[maxn];
stack<int> S;

bool can[maxn], ok[maxn];
int tmp[maxn], color[maxn];

void init()
{
    memset(head, -1, sizeof head);
    memset(pre, 0, sizeof pre);
    memset(bel, 0, sizeof bel);
    memset(ins, 0, sizeof ins);
    dfn=block=tot=0;
}

void AddEdge(int u, int v)
{
    edge[tot]=Edge(v, head[u]);
    head[u]=tot++;
}

bool dfs(int u, int col)
{
    color[u]=col;
    for(int i=head[u]; ~i; i=edge[i].nxt)
    {
        int v=edge[i].v;
        if(!ok[v])continue ;
        if(color[v]!=-1)
        {
            if(color[v]==col)return false;
            continue ;
        }
        if(!dfs(v, !col))return false;
    }
    return true;
}


void Tarjan(int u, int fa)
{
    pre[u]=low[u]=++dfn;
    S.push(u);
    ins[u]=true;
    for(int i=head[u]; ~i; i=edge[i].nxt)
    {
        int v=edge[i].v;
        if(v==fa)continue ;
        if(!pre[v])
        {
            Tarjan(v, u);
            low[u]=min(low[u], low[v]);
            if(low[v]>=pre[u])
            {
                block++;
                int cnt=0;
                memset(ok, 0, sizeof ok);
                while(true)
                {
                    int vn=S.top();
                    S.pop();
                    tmp[cnt++]=vn;
                    ok[vn]=true;
                    ins[vn]=false;
                    bel[vn]=block;
                    if(v==vn)break;
                }
                ok[u]=true;
                memset(color, -1, sizeof color);
                color[u]=1;
                if(!dfs(u, 0))
                {
                    can[u]=true;
                    while(cnt)
                        can[tmp[--cnt]]=true;
                }
            }
        }
        else if(ins[v])
            low[u]=min(low[u], pre[v]);
    }
}

int solve()
{
    memset(can, 0, sizeof can);
    for(int i=1; i<=n; i++)
        if(!pre[i])
            Tarjan(i, -1);
    int ans=0;
    for(int i=1; i<=n; i++)
        ans+=can[i];
    return n-ans;
}

bool g[maxn][maxn];

int main()
{
    while(~scanf("%d%d", &n, &m) && n+m)
    {
        init();
        memset(g, 0, sizeof g);
        while(m--)
        {
            int u, v;
            scanf("%d%d", &u, &v);
            g[u][v]=g[v][u]=1;
        }
        for(int i=1; i<=n; i++)
            for(int j=1; j<=n; j++)
                if(i!=j && !g[i][j])
                    AddEdge(i, j);
        printf("%d\n", solve());
    }
    return 0;
}
