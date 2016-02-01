#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;
const int maxn=110000;

int n, pre[maxn], low[maxn], dfn;
vector<int> G[maxn];
vector<pair<int, int> > bridge;

void init()
{
    memset(pre, 0, sizeof pre);
    for(int i=0; i<=n; i++)
        G[i].clear();
    dfn=0;
    bridge.clear();
}

void dfs(int u, int fa)
{
    pre[u]=low[u]=++dfn;
    for(int i=0; i<G[u].size(); i++)
    {
        int v=G[u][i];
        if(!pre[v])
        {
            dfs(v, u);
            low[u]=min(low[u], low[v]);
            if(pre[u]<low[v])
            {
                if(u<v)bridge.push_back(make_pair(u, v));
                else bridge.push_back(make_pair(v, u));
            }
        }
        else if(v!=fa)
            low[u]=min(pre[v], low[u]);
    }
}

int main()
{
    while(~scanf("%d", &n))
    {
        init();
        for(int i=0; i<n; i++)
        {
            int u, v, m;
            scanf("%d (%d)", &u, &m);
            while(m--)
            {
                scanf("%d", &v);
                G[u].push_back(v);
            }
        }
        for(int i=0; i<n; i++)
            if(!pre[i])
                dfs(i, -1);
        printf("%d critical links\n", bridge.size());
        sort(bridge.begin(), bridge.end());
        for(int i=0; i<bridge.size(); i++)
            printf("%d - %d\n", bridge[i].first, bridge[i].second);
        puts("");
    }
    return 0;
}
