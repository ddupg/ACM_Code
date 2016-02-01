#include <cstdio>
#include <cstring>
using namespace std;
const int maxn = 550;

struct Edge
{
    int v, nxt;
} edge[maxn*maxn];

int head[maxn], n, m, link[maxn], tot;
bool used[maxn], g[maxn][maxn];

void init()
{
    memset(head, -1, sizeof head);
    memset(g, 0, sizeof g);
    tot=0;
}

void AddEdge(int u, int v)
{
    edge[tot].v=v;
    edge[tot].nxt=head[u];
    head[u]=tot++;
}

bool match(int u)
{
    for(int i=head[u]; ~i; i=edge[i].nxt)
    {
        int v=edge[i].v;
        if(used[v])continue ;
        used[v]=true;
        if(link[v]==-1 || match(link[v]))
        {
            link[v]=u;
            return true;
        }
    }
    return false;
}

int hungary()
{
    int ans=0;
    memset(link, -1, sizeof link);
    for(int i=1; i<=n; i++)
    {
        memset(used, 0, sizeof used);
        ans+=match(i);
    }
    return ans;
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
            g[u][v]=true;
        }
        for(int i=1; i<=n; i++)
            for(int j=1; j<=n; j++)
                for(int k=1; k<=n; k++)
                    g[i][j]=g[i][j] || (g[i][k] && g[k][j]);
        for(int i=1; i<=n; i++)
            for(int j=1; j<=n; j++)
                if(i!=j && g[i][j])
                    AddEdge(i, j);
        printf("%d\n", n-hungary());
    }
    return 0;
}
