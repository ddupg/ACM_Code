#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cstring>
#include <queue>
#include <vector>
#define mem(a, val) memset((a), (val), sizeof(a))
using namespace std;
const int maxn=220;
const int INF=1e9;
struct Edge
{
    int u, v, dis;
    Edge(int u, int v, int d):u(u), v(v), dis(d){}
};
vector<Edge> edge;
vector<int> G[maxn];
int n;

void init()
{
    for(int i=0; i<n; i++)G[i].clear();
    edge.clear();
}

void AddEdge(int u, int v, int d)
{
    edge.push_back(Edge(u, v, d));
    G[u].push_back(edge.size()-1);
}

int spfa(int s, int t)
{
    queue<int> q;
    int d[maxn], vis[maxn]={0};
    for(int i=0; i<n; i++)
        d[i]=i==s?0:INF;
    q.push(s);
    vis[s]=1;
    while(!q.empty())
    {
        int u=q.front();
        q.pop();
        vis[u]=0;
        for(int i=0; i<G[u].size(); i++)
        {
            Edge e=edge[G[u][i]];
            if(d[e.v]>d[u]+e.dis)
            {
                d[e.v]=d[u]+e.dis;
                if(!vis[e.v])
                    q.push(e.v);
            }
        }
    }
    return d[t]>=INF?-1:d[t];
}

int main()
{
    int m, s, t;
    while(~scanf("%d%d", &n, &m))
    {
        init();
        while(m--)
        {
            int u, v, dis;
            scanf("%d%d%d", &u, &v, &dis);
            AddEdge(u, v, dis);
            AddEdge(v, u, dis);
        }
        scanf("%d%d", &s, &t);
        printf("%d\n", spfa(s, t));
    }
    return 0;
}
