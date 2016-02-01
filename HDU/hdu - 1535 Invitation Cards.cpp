#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <queue>
#include <vector>
#include <cstring>
using namespace std;
const int maxn=1000000+10;
const int INF=1e9+100;

struct Edge
{
    int u, v, d;
    Edge(int u=0, int v=0, int d=0):u(u), v(v), d(d){}
};
struct qnode
{
    int u, d;
    qnode(int u, int d):u(u), d(d){};
    bool operator < (const qnode x)const
    {
        return d>x.d;
    }
};

struct Dijkstra
{
    int d[maxn], n, m;
    Edge edge[maxn];
    int head[maxn], next[maxn];
    void init(int n)
    {
        this->n=n;
        m=0;
        memset(head, -1, sizeof(head));
    }
    void AddEdge(int u, int v, int d)
    {
        edge[m]=Edge(u, v, d);
        next[m]=head[u];
        head[u]=m++;
    }
    int dijkstra(int s)
    {
        priority_queue<qnode> q;
        bool vis[maxn]={0};
        for(int i=1; i<=n; i++)
            d[i]=i==s?0:INF;
        q.push(qnode(s, 0));
        while(!q.empty())
        {
            qnode x=q.top();
            q.pop();
            if(vis[x.u])continue ;
            vis[x.u]=1;
            for(int i=head[x.u]; ~i; i=next[i])
            {
                Edge& e=edge[i];
                if(d[e.v]>d[x.u]+e.d)
                {
                    d[e.v]=d[x.u]+e.d;
                    q.push(qnode(e.v, d[e.v]));
                }
            }
        }
        int ans=0;
        for(int i=1; i<=n; i++)
            ans+=d[i];
        return ans;
    }
}dij1, dij2;

int main()
{
    int T;
    scanf("%d", &T);
    while(T--)
    {
        int n, m;
        scanf("%d%d", &n, &m);
        dij1.init(n);
        dij2.init(n);
        while(m--)
        {
            int u, v, d;
            scanf("%d%d%d", &u, &v, &d);
            dij1.AddEdge(u, v, d);
            dij2.AddEdge(v, u, d);
        }
        printf("%d\n", dij1.dijkstra(1)+dij2.dijkstra(1));
    }
    return 0;
}
