#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <queue>
#include <vector>
using namespace std;
const int maxn=200000+10;
const int oo = 0x3f3f3f3f;

struct Edge
{
    int u, v, d;
    Edge(int u=0, int v=0, int d=0):u(u), v(v), d(d){}
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
    int n, m, tot;
    int tail[maxn<<1], next[maxn<<2];
    int d[maxn<<1];
    Edge edge[maxn<<2];
    bool vis[maxn<<1];

    void init()
    {
        tot=0;
        memset(tail, -1, sizeof tail);
        memset(vis, 0, sizeof vis);
        memset(d, 0x3f, sizeof d);
    }

    void AddEdge(int u, int v, int dis)
    {
        edge[++tot]=Edge(u, v, dis);
        next[tot]=tail[u];
        tail[u]=tot;
    }

    int dijkstra(int s, int t)
    {
        d[s]=0;
        priority_queue<qnode> q;
        q.push(qnode(s, 0));
        while(!q.empty())
        {
            qnode x=q.top();
            q.pop();
            if(vis[x.u])continue ;
            vis[x.u]=true;
            if(x.u==t)return d[t];
            for(int i=tail[x.u]; ~i; i=next[i])
            {
                Edge& e=edge[i];
                if(d[e.v]>d[x.u]+e.d)
                {
                    d[e.v]=d[x.u]+e.d;
                    q.push(qnode(e.v, d[e.v]));
                }
            }
        }
        return -1;
    }
} solver;

int bel[maxn], n, m, C;

int main()
{
    int T, kase=0;
    scanf("%d", &T);
    while(T--)
    {
        solver.init();
        scanf("%d%d%d", &n, &m, &C);
        for(int i=1; i<=n; i++)
        {
            scanf("%d", bel+i);
            solver.AddEdge(bel[i]+n, i, 0);
            solver.AddEdge(i, bel[i]+n+1, C);
            solver.AddEdge(i, bel[i]+n-1, C);
        }
        while(m--)
        {
            int u, v, dis;
            scanf("%d%d%d", &u, &v, &dis);
            solver.AddEdge(u, bel[v]+n, dis);
            solver.AddEdge(v, bel[u]+n, dis);
        }
        printf("Case #%d: %d\n", ++kase, solver.dijkstra(1, n));
    }
    return 0;
}
