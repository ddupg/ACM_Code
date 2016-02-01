#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cstring>
#include <vector>
using namespace std;
const int maxn=4000+10;
int bcc[maxn];
vector<int> G[maxn];
int g[111][111];
int N, M, n;
int cnt, bcc_num[maxn];

void dfs(int u, int num)
{
    bcc_num[u]=num;
    bcc[num]++;
    for(int i=0; i<G[u].size(); i++)
        if(!bcc_num[G[u][i]])
            dfs(G[u][i], num);
}

void solve()
{
    cnt=0;
    memset(bcc_num, 0, sizeof(bcc_num));
    for(int i=1; i<=n; i++)
        if(!bcc_num[i])
        {
            bcc[++cnt]=0;
            dfs(i, cnt);
        }

    int ans=0;
    for(int i=1; i<=cnt; i++)
        ans+=bcc[i]/2;
    printf("%d\n", ans);
}

int main()
{
    while(~scanf("%d%d", &N, &M) && N+M)
    {
        memset(g, 0, sizeof(g));
        for(int i=0; i<maxn; i++)
            G[i].clear();
        n=0;
        while(N--)
        {
            int x, y, u, v;
            scanf("%d%d", &x, &y);
            if(!g[x][y])
            {
                g[x][y]=++n;
                u=n;
            }
            else u=g[x][y];
            if(!g[x+1][y])
            {
                g[x+1][y]=++n;
                v=n;
            }
            else v=g[x+1][y];
            G[u].push_back(v);
            G[v].push_back(u);
        }
        while(M--)
        {
            int x, y, u, v;
            scanf("%d%d", &x, &y);
            if(!g[x][y])
            {
                g[x][y]=++n;
                u=n;
            }
            else u=g[x][y];
            if(!g[x][y+1])
            {
                g[x][y++]=++n;
                v=n;
            }
            else v=g[x][y+1];
            G[u].push_back(v);
            G[v].push_back(u);
        }
        solve();
    }
    return 0;
}
