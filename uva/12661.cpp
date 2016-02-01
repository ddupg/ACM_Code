#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>
#include <algorithm>
#define mem(a, val) memset(a, val, sizeof a)
using namespace std;
const int maxn=350;
const int oo=0x3f3f3f3f;

struct Edge
{
    int u, v, w, a, b;
    Edge(int u, int v, int a, int b, int w):u(u), v(v), a(a), b(b), w(w){}
};
struct qnode
{
    int u, w;
    qnode(int u, int w):u(u), w(w){}
    bool operator < (const qnode a)const
    {
        return w>a.w;
    }
};
int n, d[maxn];
vector<int> G[maxn];
vector<Edge> edge;
bool vis[maxn];
void init()
{
    for(int i=0; i<=n; i++)
        G[i].clear();
    edge.clear();
    mem(d, 0x3f);
    mem(vis, 0);
}
void AddEdge(int u, int v, int a, int b, int w)
{
    G[u].push_back(edge.size());
    edge.push_back(Edge(u, v, a, b, w));
}
int GetDist(int t, Edge e)
{
    t%=(e.a+e.b);
    if(t+e.w<=e.a)
        return e.w;
    if(e.w<=e.a)
        return e.a+e.b-t+e.w;
    return oo;
}
int Dijkstra(int s, int t)
{
    priority_queue<qnode> q;
    d[s]=0;
    q.push(qnode(s, 0));
    while(!q.empty())
    {
        qnode x=q.top();
        q.pop();
        if(x.u==t)return d[t];
        if(vis[x.u])continue ;
        vis[x.u]=1;
        for(int i=0; i<G[x.u].size(); i++)
        {
            Edge& e=edge[G[x.u][i]];
            int tmp=d[x.u]+GetDist(d[x.u], e);
            if(d[e.v]>tmp)
            {
                d[e.v]=tmp;
                q.push(qnode(e.v, d[e.v]));
            }
        }
    }
    return d[t];
}

int main()
{
    int m, s, t, kase=0;
    while(~scanf("%d%d%d%d", &n, &m, &s, &t))
    {
        init();
        while(m--)
        {
            int u, v, w, a, b;
            scanf("%d%d%d%d%d", &u, &v, &a, &b, &w);
            AddEdge(u, v, a, b, w);
        }
        printf("Case %d: %d\n", ++kase, Dijkstra(s, t));
    }
    return 0;
}
