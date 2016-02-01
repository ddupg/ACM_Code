#include<iostream>
#include<cstdio>
#include<map>
#include<cstring>
#include<cmath>
#include<vector>
#include<algorithm>
#include<set>
#include<queue>
#define inf 1<<27
using namespace std;
const int maxn=111;
int n, m, dist[maxn], p[maxn], T, A[maxn], d[maxn][555];
vector<int> G[maxn];
struct Edge
{
    int from, to, dist;
    Edge(int from, int to, int dist):from(from), to(to), dist(dist){}
};
vector<Edge> edges;

void init()
{
    for(int i=0; i<n; i++)
        G[i].clear();
    m=0;
    edges.clear();
}

void AddEdge(int u, int v, int d)
{
    edges.push_back(Edge(u, v, d));
    m=edges.size();
    G[u].push_back(m-1);
}

void spfa(int s)
{
    int vis[maxn]={0};
    for(int i=0; i<n; i++)
        dist[i]=inf;
    dist[s]=0;
    queue<int> q;
    q.push(s);
    vis[s]=1;
    while(!q.empty())
    {
        int u=q.front();
        q.pop();
        vis[u]=0;
        for(int i=0; i<G[u].size(); i++)
        {
            Edge e=edges[G[u][i]];
            int v=e.to;
            if(dist[v]>dist[u]+e.dist)
            {
                dist[v]=dist[u]+e.dist;
                p[v]=G[u][i];
                if(!vis[v])
                {
                    q.push(v);
                    vis[v]=1;
                }
            }
        }
    }
}

void dp(int u, int fa)
{
    for(int i=0; i<=T; i++)
        d[u][i]=A[u];
    for(int i=0; i<G[u].size(); i++)
    {
        Edge e=edges[G[u][i]];
        int v=e.to;
        if(v==fa)continue ;
        dp(v, u);
        int w=e.dist*2;
        for(int i=T; i>=w; i--)
            for(int j=i-w; j>=0; j--)   //不明白的是j从i-w到0就对，反过来就不对。
                d[u][i]=max(d[u][i],d[u][j]+d[v][i-j-w]);
    }
}

int main()
{
    while(~scanf("%d%d", &n, &T))
    {
        init();
        for(int i=0; i<n-1; i++)
        {
            int u, v, dist;
            scanf("%d%d%d", &u, &v, &dist);
            --u;
            --v;
            AddEdge(u, v, dist);
            AddEdge(v, u, dist);
        }
        for(int i=0; i<n; i++)scanf("%d", &A[i]);

        spfa(0);

        for(int i=n-1; i!=0; i=edges[p[i]].from)
            edges[p[i]].dist=edges[p[i]^1].dist=0;

        T-=dist[n-1];
        if(T<0)
        {
            puts("Human beings die in pursuit of wealth, and birds die in pursuit of food!");
            continue ;
        }
        dp(0, -1);
        printf("%d\n", d[0][T]);
    }
    return 0;
}
