#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cstring>
#include <queue>
#include <vector>
using namespace std;
const int maxn=1110;
const int INF=1e9;
int n, m, d[maxn];
vector<int> G[maxn];
struct Edge
{
    int u, v, d;
    Edge(int u, int v, int d):u(u), v(v), d(d){}
};
vector<Edge> edge;

void AddEdge(int u, int v, int d)
{
    edge.push_back(Edge(u, v, d));
    G[u].push_back(edge.size()-1);
}

int spfa()
{
    bool inq[maxn]={0, 1};
    for(int i=1; i<=n; i++)
        d[i]=i==1?0:INF;
    queue<int> q;
    q.push(1);
    while(!q.empty())
    {
        int u=q.front();
        q.pop();
        inq[u]=0;
        for(int i=0; i<G[u].size(); i++)
        {
            Edge e=edge[G[u][i]];
            if(d[e.v]>d[u]+e.d)
            {
                d[e.v]=d[u]+e.d;
                if(!inq[e.v])
                {
                    inq[e.v]=1;
                    q.push(e.v);
                }
            }
        }
    }
    return d[n];
}

int main()
{
    while(~scanf("%d%d", &m, &n))
    {
        for(int i=1; i<=n; i++)G[i].clear();
        while(m--)
        {
            int u, v, d;
            scanf("%d%d%d", &u, &v, &d);
            AddEdge(u, v, d);
            AddEdge(v, u, d);
        }
        printf("%d\n", spfa());
    }
    return 0;
}
