#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>
#include <queue>
using namespace std;

const int maxn=220;
const int oo=0x3f3f3f3f;
struct Edge
{
    int u, v, cap, flow, cost;
    Edge(int u, int v, int cap, int flow, int cost):u(u), v(v), cap(cap), flow(flow), cost(cost){}
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
        for(int i=0; i<=n; i++)
            G[i].clear();
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
    bool spfa(int s, int t, int& flow, int& cost)
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
                        inq[e.v]=1;
                    }
                }
            }
        }
        if(d[t]==oo)return false;
        flow+=a[t];
        cost+=a[t]*d[t];
        int u=t;
        while(u!=s)
        {
            edge[p[u]].flow+=a[t];
            edge[p[u]^1].flow-=a[t];
            u=edge[p[u]].u;
        }
        return true;
    }
    int MinCost(int s, int t, int& flow)
    {
        int cost=0;
        flow=0;
        while(spfa(s, t, flow, cost));
        return cost;
    }
} net;

int main()
{
    int n;
    while(~scanf("%d", &n) && n)
    {
        net.init(2*n+10);
        int S=0, T=n*2+2;
        for(int i=1; i<=n; i++)
        {
            net.AddEdge(S, i, 1, 0);
            net.AddEdge(i+n, T, 1, 0);
            int v, c;
            while(scanf("%d", &v) && v)
            {
                scanf("%d", &c);
                net.AddEdge(i, v+n, 1, c);
            }
        }
        int flow;
        int ans=net.MinCost(S, T, flow);
        if(flow==n)
            printf("%d\n", ans);
        else puts("N");
    }
    return 0;
}
