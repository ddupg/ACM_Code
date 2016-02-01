#include <iostream>
#include <cstdio>
#include <cstdlib>
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
    Edge(int u, int v, int d):u(u), v(v), d(d) {}
};
struct qnode
{
    int u, d;
    qnode(int u, int d):u(u), d(d) {}
    bool operator < (const qnode x)const
    {
        return d>x.d;
    }
};
struct Dijkstra
{
    int d[maxn], n;
    vector<Edge> edge;
    vector<int> G[maxn];
    void init(int n)
    {
        this->n=n;
        for(int i=1; i<=n; i++)
            G[i].clear();
        edge.clear();
    }
    void AddEdge(int u, int v, int d)
    {
        edge.push_back(Edge(u, v, d));
        G[u].push_back(edge.size()-1);
    }
    void dijkstra(int s)
    {
        bool vis[maxn]= {0};
        for(int i=1; i<=n; i++)
            d[i]=i==s?0:INF;
        priority_queue<qnode> q;
        q.push(qnode(s, 0));
        while(!q.empty())
        {
            qnode x=q.top();
            q.pop();
            if(vis[x.u])continue ;
            vis[x.u]=1;
            for(int i=0; i<G[x.u].size(); i++)
            {
                Edge& e=edge[G[x.u][i]];
                if(d[e.v]>d[e.u]+e.d)
                {
                    d[e.v]=d[e.u]+e.d;
                    q.push(qnode(e.v, d[e.v]));
                }
            }
        }
    }
} solver;

int main()
{
    int n, m, S;
    while(~scanf("%d%d%d", &n, &m, &S))
    {
        solver.init(n);
        while(m--)
        {
            int u, v, d;
            scanf("%d%d%d", &u, &v, &d);
            solver.AddEdge(v, u, d);
        }
        solver.dijkstra(S);
        scanf("%d", &m);
        int ans=INF;
        while(m--)
        {
            int u;
            scanf("%d", &u);
            ans=min(ans, solver.d[u]);
        }
        printf("%d\n", ans==INF?-1:ans);
    }
    return 0;
}
