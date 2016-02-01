#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;
const int maxn=100000+110;

int n, m, q, pre[maxn], low[maxn], dfn, cnt, father[maxn];
bool isbridge[maxn];
vector<int> G[maxn];

void init()
{
    for(int i=0; i<=n; i++)
        G[i].clear();
    memset(pre, 0, sizeof pre);
    memset(isbridge, 0, sizeof isbridge);
    dfn=cnt=0;
}

void dfs(int u, int fa)
{
    pre[u]=low[u]=++dfn;
    for(int i=0; i<G[u].size(); i++)
    {
        int v=G[u][i];
        if(!pre[v])
        {
            father[v]=u;
            dfs(v, u);
            low[u]=min(low[u], low[v]);
            if(pre[u]<low[v])
            {
                cnt++;
                isbridge[v]=true;
            }
        }
        else if(v!=fa) low[u]=min(low[u], pre[v]);
    }
}
void LCA(int u, int v)
{
    if(u==v)return ;
    if(pre[u]>pre[v])
    {
        if(isbridge[u])cnt--, isbridge[u]=false;
        LCA(father[u], v);
    }
    else
    {
        if(isbridge[v])cnt--, isbridge[v]=false;
        LCA(u, father[v]);
    }
}

int main()
{
    int kase=0;
    while(~scanf("%d%d", &n, &m) && n+m)
    {
        init();
        int u, v;
        while(m--)
        {
            scanf("%d%d", &u, &v);
            G[u].push_back(v);
            G[v].push_back(u);
        }
        dfs(1, 0);
        scanf("%d", &q);
        printf("Case %d:\n", ++kase);
        while(q--)
        {
            scanf("%d%d", &u, &v);
            LCA(u, v);
            printf("%d\n", cnt);
        }
        puts("");
    }
    return 0;
}
