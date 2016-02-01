#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#define clr(a, x) memset(a, x, sizeof a)
#define pb push_back
using namespace std;

const int maxn=105;
const int maxnd=55*55;

int g[maxn][maxn], id1[maxn][maxn], id2[maxn][maxn];
int linker[maxnd], idx, idy;
bool vis[maxnd];
vector<int> G[maxnd];

void init()
{
    for(int i=0l; i<maxnd; i++)
        G[i].clear();
    clr(g, 0), clr(id1, 0), clr(id2, 0);
        idx=idy=0;
}

bool dfs(int u)
{
    for(int i=0; i<G[u].size(); i++)
    {
        int v=G[u][i];
        if(vis[v])continue ;
        vis[v]=true;
        if(linker[v]==-1 || dfs(linker[v]))
        {
            linker[v]=u;
            return true;
        }
    }
    return false;
}

int hungary()
{
    clr(linker, -1);
    int ans=0;
    for(int i=1; i<=idx; i++)
    {
        clr(vis, 0);
        ans+=dfs(i);
    }
    return ans;
}

int main()
{
    int T, n, m, t;
    scanf("%d", &T);
    while(T--)
    {
        scanf("%d%d", &n, &m);
        init();
        scanf("%d", &t);
        while(t--)
        {
            int x, y;
            scanf("%d%d", &x, &y);
            g[x][y]=1;
        }
        scanf("%d", &t);
        while(t--)
        {
            int x, y;
            scanf("%d%d", &x, &y);
            g[x][y]=2;
        }
        for(int i=1; i<=n; i++)
            for(int j=1; j<=m; j++)if(g[i][j]!=2 && !id1[i][j])
                {
                    ++idx;
                    for(int k=j; k<=m && g[i][k]!=2; k++)
                            id1[i][k]=idx;
                }
        for(int j=1; j<=m; j++)
            for(int i=1; i<=n; i++)if(g[i][j]!=2 && !id2[i][j])
                {
                    ++idy;
                    for(int k=i; k<=n && g[k][j]!=2; k++)
                            id2[k][j]=idy;
                }
        for(int i=1; i<=n; i++)
            for(int j=1; j<=m; j++)
                if(g[i][j]==1)
                    G[id1[i][j]].pb(id2[i][j]);
        printf("%d\n", hungary());
    }
    return 0;
}
