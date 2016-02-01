#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cstring>
#include <queue>
#include <vector>
using namespace std;
const int maxn=1110;
const int INF=0x3f3f3f3f;
struct Edge
{
    int u, v, dis;
    Edge(int u, int v, int d):u(u), v(v), dis(d){}
};
struct qnode
{
    int u, dis;
    qnode(int u, int d):u(u), dis(d){}
    bool operator < (const qnode x)const
    {
        return dis>x.dis;
    }
};
vector<int> G[maxn], S, T;
vector<Edge> edge;
int n, d[maxn];
void init()
{
    for(int i=1; i<=1000; i++)
        G[i].clear();
    edge.clear();
    S.clear();
    T.clear();
}
void AddEdge(int u, int v, int d)
{
    edge.push_back(Edge(u, v, d));
    G[u].push_back(edge.size()-1);
}
int Dijkstra(int s)
{
    int vis[maxn]={0}, d[maxn], res=INF;
    for(int i=1; i<=1000; i++)
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
            Edge e=edge[G[x.u][i]];
            if(d[e.v]>d[e.u]+e.dis)
            {
                d[e.v]=d[e.u]+e.dis;
                q.push(qnode(e.v, d[e.v]));
            }
        }
    }
    for(int i=0; i<T.size(); i++)
        res=min(res, d[T[i]]);
    return res;
}

int main()
{
    int m, cnts, cntd, x;
    while(~scanf("%d%d%d", &m, &cnts, &cntd))
    {
        init();
        while(m--)
        {
            int u, v, d;
            scanf("%d%d%d", &u, &v, &d);
            AddEdge(u, v, d);
            AddEdge(v, u, d);
        }
        while(cnts-- && scanf("%d", &x))
            S.push_back(x);
        while(cntd-- && scanf("%d", &x))
            T.push_back(x);
        int ans=INF;
        for(int i=0; i<S.size(); i++)
            ans=min(ans, Dijkstra(S[i]));
        printf("%d\n", ans);
    }
    return 0;
}
