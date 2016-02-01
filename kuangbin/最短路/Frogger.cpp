#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cstring>
#include <vector>
#include <cmath>
#include <queue>
using namespace std;
const int maxn=220;
const double INF=1e10;
struct Point
{
    double x, y;
} p[maxn];
struct Edge
{
    int u, v;
    double d;
    Edge(int u, int v, double d):u(u), v(v), d(d) {}
};
struct qnode
{
    int u;
    double d;
    qnode(int u, int d):u(u), d(d) {}
    bool operator < (const qnode a)const
    {
        return d>a.d;
    }
};
int n;
vector<Edge> edge;
vector<int> G[maxn];

double dis(Point a, Point b)
{
    return sqrt((a.x-b.x)*(a.x-b.x) + (a.y-b.y)*(a.y-b.y));
}

void AddEdge(int u, int v, double d)
{
    edge.push_back(Edge(u, v, d));
    G[u].push_back(edge.size()-1);
    edge.push_back(Edge(v, u, d));
    G[v].push_back(edge.size()-1);
}

void build(double dist)
{
    double tmp;
    edge.clear();
    for(int i=1; i<=n; i++)G[i].clear();
    for(int i=1; i<=n; i++)
        for(int j=1; j<i; j++)
            if(tmp=dis(p[i], p[j])<dist)
                AddEdge(i, j, tmp);
}

bool Dijkstra(double dist)
{
    build(dist);
    bool vis[maxn]={0};
    double d[maxn];
    for(int i=1; i<=n; i++)
        d[i]=i==1?0:INF;
    priority_queue<qnode> q;
    q.push(qnode(1, 0));
    while(!q.empty())
    {
        qnode x=q.top();
        q.pop();
        if(vis[x.u])continue ;
        if(x.u==2 || x.d>=INF)break;
        vis[x.u]=1;
        for(int i=0; i<G[x.u].size(); i++)
        {
            Edge & e=edge[G[x.u][i]];
            if(d[e.v]>d[x.u]+e.d)
            {
                d[e.v]=d[x.u]+e.d;
                q.push(qnode(e.v, d[e.v]));
            }
        }
    }
    return d[2]<INF;
}

int main()
{
    int kase=0;
    while(scanf("%d", &n) && n)
    {
        for(int i=1; i<=n; i++)
            scanf("%lf%lf", &p[i].x, &p[i].y);
        double L=0, R=dis(p[1], p[2]);
        while(R-L>1e-5)
        {
            double mid=(R+L)/2;
            if(Dijkstra(mid))
                R=mid;
            else L=mid;
        }
        printf("Scenario #%d\nFrog Distance = %.3lf\n\n", ++kase, L);
    }
    return 0;
}
