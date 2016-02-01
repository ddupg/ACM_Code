#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cstring>
#include <queue>
#include <vector>
using namespace std;
typedef long long LL;
const int maxn=220;
const LL oo=1LL<<50;

struct Edge
{
    int u, v;
    LL cap, flow;
    LL cost;
    Edge(int u, int v, LL c, LL f, LL co):u(u), v(v), cap(c), flow(f), cost(co) {}
};
struct MCMF
{
    int n, m, s, t;
    vector<Edge> edge;
    vector<int> G[maxn];
    int inq[maxn] ,p[maxn];
    LL a[maxn];
    LL d[maxn];
    void init(int n)
    {
        this->n=n;
        for(int i=0; i<=n; i++)
            G[i].clear();
        edge.clear();
    }
    int AddEdge(int u, int v, LL cap, LL cost)
    {
        edge.push_back(Edge(u, v, cap, 0, cost));
        edge.push_back(Edge(v, u, 0, 0, -cost));
        m=edge.size();
        G[u].push_back(m-2);
        G[v].push_back(m-1);
        return m-2;
    }

    bool Spfa(int s, int t, LL & flow, LL & cost)
    {
        for(int i=0; i<=n; i++)d[i]=oo;
        memset(inq, 0, sizeof inq);
        d[s]=0, inq[s]=true, p[s]=0, a[s]=1e9;

        queue<int> q;
        q.push(s);
        while(!q.empty())
        {
            int u=q.front();
            q.pop();
            inq[u]=false;
            for(int i=0; i<G[u].size(); i++)
            {
                Edge& e=edge[G[u][i]];
                if(e.cap>e.flow && d[e.v]>d[u]+e.cost)
                {
                    d[e.v]=d[u]+e.cost;
                    p[e.v]=G[u][i];
                    a[e.v]=min(a[u], e.cap-e.flow);
                    if(!inq[e.v])
                    {
                        q.push(e.v);
                        inq[e.v]=true;
                    }
                }
            }
        }
        if(d[t]==oo)
            return false;
        flow+=a[t];
        cost+=d[t]*a[t];
        int u=t;
        while(u!=s)
        {
            edge[p[u]].flow+=a[t];
            edge[p[u]^1].flow-=a[t];
            u=edge[p[u]].u;
        }
        return true;
    }

    LL Mincost(int s, int t)
    {
        LL flow=0;
        LL cost=0;
        while(Spfa(s, t, flow, cost));
        return cost;
    }
} solver;

int id[maxn][maxn];
struct Point
{
    long long x, y;
} w[maxn], b[maxn];

LL dist(int i, int j)
{
    return (w[i].x-b[j].x)*(w[i].x-b[j].x)+(w[i].y-b[j].y)*(w[i].y-b[j].y);
}

int main()
{
    int n, kase=0;
    while(~scanf("%d", &n))
    {
        solver.init(2*n+10);
        for(int i=1; i<=n; i++)
            scanf("%lld%lld", &w[i].x, &w[i].y);
        for(int i=1; i<=n; i++)
            scanf("%lld%lld", &b[i].x, &b[i].y);
        for(int i=1; i<=n; i++)
            for(int j=1; j<=n; j++)
                id[i][j]=solver.AddEdge(i, j+n, n, dist(i, j));
        for(int i=1; i<=n; i++)
        {
            solver.AddEdge(0, i, 1, 0);
            solver.AddEdge(i+n, 2*n+1, 1, 0);
        }
        solver.Mincost(0, 2*n+1);

        if(kase++)
            puts("");
        for(int i=1; i<=n; i++)
            for(int j=1; j<=n; j++)
                if(solver.edge[id[i][j]].flow==1)
                {
                    printf("%d\n", j);
                    break;
                }
    }
    return 0;
}
