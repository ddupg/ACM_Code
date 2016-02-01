#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <set>
#include <vector>
#include <algorithm>
#include <cmath>
#include <cstring>
using namespace std;
const int maxn=1111;
int n, m, pre[maxn], low[maxn], dfs_clock;
int g[maxn][maxn], w[maxn][maxn];
vector<int> G[maxn];
vector<pair<int, int> > ans;

int dfs(int u, int fa)
{
    int lowu=pre[u]= ++dfs_clock;

    int child=0;
    for(int i=0; i<G[u].size(); i++)
    {
        int v=G[u][i];
        if(!pre[v])
        {
            child++;
            int lowv=dfs(v, u);
            lowu=min(lowu, lowv);
            if(lowv>lowu && g[u][v]==1)
                ans.push_back(make_pair(u, v));

        }
        else if(pre[v]<pre[u] && v!=fa)
            lowu=min(lowu, pre[v]);
    }
    return low[u]=lowu;
}

int main()
{
    while(~scanf("%d%d", &n, &m) && m+n)
    {
        for(int i=0; i<=n; i++)
            G[i].clear();
        ans.clear();
        memset(g, 0, sizeof(g));
        for(int i=0; i<m; i++)
        {
            int a, b, tw;
            scanf("%d%d%d", &a, &b, &tw);
            w[a][b]=w[b][a]=tw;
            G[a].push_back(b);
            G[b].push_back(a);
            ++g[a][b];
            ++g[b][a];
        }

        memset(pre, 0, sizeof(pre));
        dfs(1, -1);
        int ok=1;
        for(int i=1; i<=n; i++)
            if(!pre[i])
            {
                ok=0;
                break;
            }
        if(!ok)
        {
            printf("0\n");
            continue ;
        }

        int res=1e9;
        for(int i=0; i<ans.size(); i++)
        {
            int x=ans[i].first, y=ans[i].second;
            res=min(res, w[x][y]);
        }
        if(res==1e9)
            printf("-1\n");
        else if(res==0)
            printf("1\n");
        else printf("%d\n", res);
    }
    return 0;
}
