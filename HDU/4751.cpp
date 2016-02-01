#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <vector>
using namespace std;

int n, g[111][111], vis[111];

int bipartite(int u)
{
    for(int i=1; i<=n; i++)
    {
        if(g[u][i] || i==u)continue ;
        if(vis[i]==vis[u])return 0;
        if(!vis[i])
        {
            vis[i]=3-vis[u];
            if(!bipartite(i))return 0;
        }
    }
    return 1;
}

int main()
{
    while(scanf("%d", &n)!=EOF)
    {
        memset(g, 0, sizeof(g));
        memset(vis, 0, sizeof(vis));
        for(int i=1; i<=n; i++)
        {
            int v;
            while(scanf("%d", &v) && v)
                g[i][v]=1;
        }
        for(int i=1; i<=n; i++)
        {
            g[i][i]=1;
            for(int j=i+1; j<=n; j++)
            {
                if(!g[i][j] || !g[j][i])
                    g[i][j]=g[j][i]=0;
            }
        }

        int ok=1;
        for(int i=1; i<=n && ok; i++)
            if(!vis[i])
            {
                vis[i]=1;
                if(!bipartite(i))
                {
                    ok=0;
                    break;
                }
            }

        if(ok)
            puts("YES");
        else puts("NO");
    }
    return 0;
}
