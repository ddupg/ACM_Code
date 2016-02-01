#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <queue>
#include <algorithm>
#define mem(a, val) memset((a), (val), sizeof(a))
using namespace std;
const int maxn=1010;
const int INF=0x3f3f3f3f;
struct Edge
{
    int u, v, dis, cost;
    Edge(int u, int v, int d, int c):u(u), v(v), dis(d), cost(c){}
};
struct qnode
{
    int u, dis, cost;
    qnode(int u, int d, int c):u(u), dis(d), cost(c){}
    bool operator < (const qnode x)const
    {
        return dis>x.dis || (dis==x.dis && cost>x.cost);
    }
};
int n, m, cnt;
vector<int> G[maxn];
vector<Edge> edge;

void init()
{
    for(int i=1; i<=n; i++)
        G[i].clear();
    edge.clear();
}

void AddEdge(int u, int v, int d, int c)
{
    edge.push_back(Edge(u, v, d, c));
    edge.push_back(Edge(v, u, d, c));
    G[u].push_back(edge.size()-2);
    G[v].push_back(edge.size()-1);
}

void Dijkstra(int s, int t)
{
    int vis[maxn]={0};
    int d[maxn], c[maxn];
    for(int i=1; i<=n; i++)
        d[i]=c[i]=i==s?0:INF;
    priority_queue<qnode> q;
    q.push(qnode(s, 0, 0));
    while(!q.empty())
    {
        qnode x=q.top();
        q.pop();
        vis[x.u]=1;
        for(int i=0; i<G[x.u].size(); i++)
        {
            Edge e=edge[G[x.u][i]];
            if(d[e.v]>d[x.u]+e.dis)
            {
                d[e.v]=d[x.u]+e.dis;
                c[e.v]=c[x.u]+e.cost;
                q.push(qnode(e.v, d[e.v], c[e.v]));
            }
            else if(d[e.v]==d[x.u]+e.dis && c[e.v]>d[x.u]+e.cost)
            {
                c[e.v]=c[x.u]+e.cost;
                q.push(qnode(e.v, d[e.v], c[e.v]));
            }
        }
    }
    printf("%d %d\n", d[t], c[t]);
}

int main()
{
    while(~scanf("%d%d", &n, &m) && n+m)
    {
        init();
        while(m--)
        {
            int u, v, d, c;
            scanf("%d%d%d%d", &u, &v, &d, &c);
            AddEdge(u, v, d, c);
        }
        int s, t;
        scanf("%d%d", &s, &t);
        Dijkstra(s, t);
    }
    return 0;
}
