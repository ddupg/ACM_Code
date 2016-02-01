#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
using namespace std;
const int maxn=550;

vector<int> G[maxn];
bool g[maxn][maxn];
int n, m, link[maxn];
bool used[maxn];

bool dfs(int u)
{
    for(int i=0; i<G[u].size(); i++)
    {
        int v=G[u][i];
        if(used[v])continue ;
        used[v]=1;
        if(link[v]==-1 || dfs(link[v]))
        {
            link[v]=u;
            return true;
        }
    }
    return false;
}

int hungary()
{
    memset(link, -1, sizeof link);
    int ans=0;
    for(int u=1; u<=n; u++)
    {
        memset(used, 0, sizeof used);
        ans+=dfs(u);
    }
    return ans;
}

int main()
{
    while(~scanf("%d%d", &n, &m) && n+m)
    {
        for(int i=1; i<=n; i++)
            G[i].clear();
        memset(g, 0, sizeof g);
        while(m--)
        {
            int u, v;
            scanf("%d%d", &u, &v);
            g[u][v]=1;
        }
        for(int i=1; i<=n; i++)
            g[i][i]=1;
        for(int k=1; k<=n; k++)
            for(int i=1; i<=n; i++)
                for(int j=1; j<=n; j++)
                    g[i][j]=(g[i][j] || (g[i][k] && g[k][j]));
        for(int i=1; i<=n; i++)
            for(int j=1; j<=n; j++)
                if(i!=j && g[i][j])
                    G[i].push_back(j);
        printf("%d\n", n-hungary());
    }
    return 0;
}
