#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <queue>
#include <vector>
#include <cstring>
#include <map>
using namespace std;
const int maxn=155;
const int INF=0x3f3f3f3f;
int d[maxn], n, m, S, T;
map<string, int> g;
struct Edge
{
    int u, v, dis;
    Edge(int u, int v, int dis):u(u), v(v), dis(dis){}
};
struct qnode
{
    int u, dis;
    qnode(int u, int dis):u(u), dis(dis){}
    bool operator < (const qnode x)const
    {
        return dis>x.dis;
    }
};
vector<Edge> edge;
vector<int> G[maxn];
void AddEdge(int u, int v, int d)
{
    edge.push_back(Edge(u, v, d));
    G[u].push_back(edge.size()-1);
}
void init()
{
    n=0;
    g.clear();
    edge.clear();
    for(int i=1; i<=150; i++)
        G[i].clear();
}
int getid(string s)
{
    if(g.count(s))
        return g[s];
    g[s]=++n;
    return n;
}
void input()
{
    char s1[33], s2[33];
    int dis;
    scanf("%s%s", s1, s2);
    S=getid(s1);
    T=getid(s2);
    while(m--)
    {
        scanf("%s%s%d", s1, s2, &dis);
        int u=getid(s1), v=getid(s2);
        AddEdge(u, v, dis);
        AddEdge(v, u, dis);
    }
}

int Dijkstra()
{
    int vis[maxn]={0};
    for(int i=1; i<=n; i++)
        d[i]=i==S?0:INF;
    priority_queue<qnode> q;
    q.push(qnode(S, 0));
    while(!q.empty())
    {
        qnode x=q.top();
        q.pop();
        if(x.dis>=INF)return -1;
        if(x.u==T)return x.dis;
        if(vis[x.u])continue ;
        vis[x.u]=1;
        for(int i=0; i<G[x.u].size(); i++)
        {
            Edge e=edge[G[x.u][i]];
            if(d[e.v]>d[x.u]+e.dis)
            {
                d[e.v]=d[x.u]+e.dis;
                q.push(qnode(e.v, d[e.v]));
            }
        }
    }
    return -1;
}

int main()
{
    while(scanf("%d", &m) && (~m))
    {
        init();
        input();
        printf("%d\n", Dijkstra());
    }
    return 0;
}
