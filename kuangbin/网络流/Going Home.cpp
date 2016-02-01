#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;
const int maxn=10010;
const int oo = 0x3f3f3f3f;

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

    int Mincost(int s, int t)
    {
        int flow=0, cost=0;
        while(SPFA(s, t, flow, cost))
            ;
        return cost;
    }
} net;

char g[110][110];
int n, m;
vector<pair<int, int> > a, b;

int getDist(pair<int, int> a, pair<int, int> b)
{
    return abs(a.first-b.first)+abs(a.second-b.second);
}

int main()
{
    while(~scanf("%d%d", &n, &m) && n+m)
    {
        a.clear();
        b.clear();
        for(int i=0; i<n; i++)
        {
            scanf("%s", g[i]);
            for(int j=0; j<m; j++)
            {
                if(g[i][j]=='H')
                    a.push_back(make_pair(i, j));
                else if(g[i][j]=='m')
                    b.push_back(make_pair(i, j));
            }
        }
        int S=0, T=a.size()+b.size()+2;
        net.init(a.size()+b.size()+2);
        for(int i=0; i<a.size(); i++)
            net.AddEdge(S, i+1, 1, 0);
        for(int i=0; i<b.size(); i++)
            net.AddEdge(i+1+a.size(), T, 1, 0);
        for(int i=0; i<a.size(); i++)
            for(int j=0; j<=b.size(); j++)
                net.AddEdge(i+1, j+1+a.size(), 1, getDist(a[i], b[j]));
        printf("%d\n", net.Mincost(S, T));
    }
    return 0;
}
