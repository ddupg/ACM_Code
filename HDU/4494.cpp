#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <queue>
#include <vector>
using namespace std;
const int maxn=500;
const int oo=0x3f3f3f3f;

struct Edge
{
    int u, v, cap, flow, cost;
    Edge(int u, int v, int cap, int f, int cost):u(u), v(v), cap(cap), flow(f), cost(cost) {}
};
struct MCMF
{
    int n, m, s, t;
    vector<Edge> edge;
    vector<int> G[maxn];
    int inq[maxn], d[maxn], p[maxn], a[maxn];
    void init(int n)
    {
        this->n=n;
        for(int i=0; i<=n; i++)G[i].clear();
        edge.clear();
    }
    void AddEdge(int u, int v, int cap, int cost)
    {
        edge.push_back(Edge(u, v, cap, 0, cost));
        edge.push_back(Edge(v, u, 0, 0, -cost));
        m=edge.size();
        G[u].push_back(m-2);
        G[v].push_back(m-1);
    }
    bool SPFA(int s, int t, int& flow, int& cost)
    {
        memset(d, 0x3f, sizeof d);
        memset(inq, 0, sizeof inq);
        d[s]=0, inq[s]=1, p[s]=0, a[s]=oo;

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
                        inq[e.v]=true;
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
    int MinCost(int s, int t)
    {
        int flow=0, cost=0;
        while(SPFA(s, t, flow, cost))
            ;
        return cost;
    }
} net;

struct Node
{
    int st, cost, v[10];
    double x, y;
} nd[maxn];

double sqr(double x)
{
    return x*x;
}

bool g[maxn][maxn];

int main()
{
    int T, n, m;
    scanf("%d", &T);
    while(T--)
    {
        scanf("%d%d", &n, &m);
        scanf("%lf%lf", &nd[0].x, &nd[0].y);
        for(int i=1; i<n; i++)
        {
            scanf("%lf%lf%d%d", &nd[i].x, &nd[i].y, &nd[i].st, &nd[i].cost);
            for(int j=0; j<m; j++)
                scanf("%d", &nd[i].v[j]);
        }
        memset(g, 0, sizeof g);
        for(int i=1; i<n; i++)
            for(int j=1; j<n; j++)
                if(i!=j && nd[i].st+nd[i].cost+sqrt(sqr(nd[i].x-nd[j].x)+sqr(nd[i].y-nd[j].y))<=nd[j].st)
                    g[i][j]=1;
        int ans=0;
        for(int k=0; k<m; k++)
        {
            int SS=0, ST=3*n+1;
            net.init(3*n+10);
            for(int i=1; i<n; i++)
            {
                net.AddEdge(SS, i, nd[i].v[k], 1);
                net.AddEdge(i, i+n, nd[i].v[k], 0);
                net.AddEdge(SS, i+n*2, nd[i].v[k], 0);
                net.AddEdge(i+n, ST, nd[i].v[k], 0);
                for(int j=1; j<n; j++)
                    if(g[i][j])
                        net.AddEdge(i+n*2, j+n, nd[i].v[k], 0);
            }
            ans+=net.MinCost(SS, ST);
        }
        printf("%d\n", ans);
    }
    return 0;
}
