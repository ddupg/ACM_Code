#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <queue>
#include <vector>
using namespace std;
const int maxn=1100;
const int INF=0x3f3f3f3f;

struct Edge
{
    int u, v, d;
    Edge(int u, int v, int d):u(u), v(v), d(d){}
};
struct qnode
{
    int u, d;
    qnode(int u, int d):u(u), d(d){}
    bool operator < (const qnode a)const
    {
        return d>a.d;
    }
};

struct Dijkstra
{
    int n;
    vector<int> G[maxn];
    vector<Edge> edge;
    int d[maxn];
    bool vis[maxn];
    void init(int n)
    {
        this->n=n;
        for(int i=1; i<=n; i++)
        {
            G[i].clear();
            vis[i]=0;
            d[i]=INF;
        }
        edge.clear();
    }
    void AddEdge(int u, int v, int d)
    {
        G[u].push_back(edge.size());
        edge.push_back(Edge(u, v, d));
    }
    void dijkstra(int s)
    {
        priority_queue<qnode> q;
        d[s]=0;
        q.push(qnode(s, 0));
        while(!q.empty())
        {
            qnode x=q.top();
            q.pop();

            if(vis[x.u])continue ;
            vis[x.u]=true;
            for(int i=0; i<G[x.u].size(); i++)
            {
                Edge& e=edge[G[x.u][i]];
                if(d[e.v]>d[x.u]+e.d)
                {
                    d[e.v]=d[x.u]+e.d;
                    q.push(qnode(e.v, d[e.v]));
                }
            }
        }
    }
}dij1, dij2;

int main()
{
    int n, m, s;
    while(~scanf("%d%d%d", &n, &m, &s))
    {
        dij1.init(n);
        dij2.init(n);
        while(m--)
        {
            int u, v, d;
            scanf("%d%d%d", &u, &v, &d);
            dij1.AddEdge(u, v, d);
            dij2.AddEdge(v, u, d);
        }
        dij1.dijkstra(s);
        dij2.dijkstra(s);
        int ans=0;
        for(int i=1; i<=n; i++)
            ans=max(ans, dij1.d[i]+dij2.d[i]);
        printf("%d\n", ans);
    }
    return 0;
}
