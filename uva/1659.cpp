#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <queue>
#include <cstring>
#include <cmath>
using namespace std;
const int maxn=220;
const double oo = 1e9;

struct Edge
{
    int u, v, cap, flow;
    double cost;
    Edge(int u, int v, int cap, int flow, double cost):u(u), v(v), cap(cap), flow(flow), cost(cost) {}
};
struct MCMF
{
    int n, m, s, t;
    vector<Edge> edge;
    vector<int> G[maxn];
    int inq[maxn], p[maxn], a[maxn];
    double d[maxn];
    void init(int n)
    {
        this->n=n;
        for(int i=0; i<n; i++)
            G[i].clear();
        edge.clear();
    }
    void AddEdge(int u, int v, int cap, double cost)
    {
        edge.push_back(Edge(u, v, cap, 0, cost));
        edge.push_back(Edge(v, u, 0, 0, -cost));
        m=edge.size();
        G[u].push_back(m-2);
        G[v].push_back(m-1);
    }
    bool spfa(int s, int t, int& flow, double& cost)
    {
        for(int i=0; i<=n; i++)
            d[i]=oo;
        memset(inq, 0, sizeof inq);
        d[s]=0, inq[s]=1, p[s]=0, a[s]=1e9;

        queue<int> q;
        q.push(s);
        while(!q.empty())
        {
            int u=q.front();
            q.pop();
            inq[u]=0;
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
                        inq[e.v]=1;
                    }
                }
            }
        }
        if(d[t]==oo)return false;
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
    double MinCost(int s, int t)
    {
        int flow=0;
        double cost=0;
        while(spfa(s, t, flow, cost));
        return cost;
    }
} net;

pair<int, int> p[maxn];
vector<int> G[maxn];
int deg[maxn];

double GetDist(double x1, double y1, double x2, double y2)
{
    return sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2));
}

int main()
{
    int n, x, y, kase=0;
    while(~scanf("%d", &n) && n)
    {
        net.init(n+10);
        scanf("%d%d", &x, &y);
        for(int i=1; i<=n; i++)
        {
            scanf("%d%d", &p[i].first, &p[i].second);
            int v;
            G[i].clear();
            while(scanf("%d", &v) && v)
                G[i].push_back(v);
        }
        double sum=0;
        memset(deg, 0, sizeof deg);
        for(int u=1; u<=n; u++)
        {
            for(int j=0; j<G[u].size(); j++)
            {
                int v=G[u][j];
                double dist=y-x*GetDist(p[u].first, p[u].second, p[v].first, p[v].second);
                if(dist<0)
                {
                    sum+=dist;
                    net.AddEdge(v, u, 1, -dist);
                    deg[v]++, deg[u]--;
                }
                else net.AddEdge(u, v, 1, dist);
            }
        }
        int S=0, T=n+1;
        for(int i=1 ;i<=n; i++)
        {
            if(deg[i]>0)
                net.AddEdge(S, i, deg[i], 0);
            if(deg[i]<0)
                net.AddEdge(i, T, -deg[i], 0);
        }
        printf("Case %d: %.2lf\n", ++kase, -(sum+net.MinCost(S, T))+1e-9);
    }
    return 0;
}
