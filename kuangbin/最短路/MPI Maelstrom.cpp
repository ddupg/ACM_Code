#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <queue>
#include <vector>
using namespace std;
const int maxn=110;
const int oo=1e9;

struct Edge
{
    int u, v, d;
    Edge(int u, int v, int d):u(u), v(v), d(d) {}
};
struct qnode
{
    int u, d;
    qnode(int u, int d):u(u), d(d) {}
    bool operator < (const qnode a)const
    {
        return d>a.d;
    }
};
int n, d[maxn];
vector<Edge> edge;
vector<int> G[maxn];

int change(char* s)
{
    int ans=0;
    while(*s)
        ans=ans*10+*(s++)-'0';
    return ans;
}

void init()
{
    for(int i=1; i<=n; i++)
        G[i].clear(), d[i]=oo;
    edge.clear();
}
void AddEdge(int u, int v, int dis)
{
    G[u].push_back(edge.size());
    edge.push_back(Edge(u, v, dis));
}

void Dijkstra()
{
    d[1]=0;
    bool vis[maxn]= {0};
    priority_queue<qnode> q;
    q.push(qnode(1, 0));
    while(!q.empty())
    {
        qnode x=q.top();
        q.pop();
        if(vis[x.u])continue ;
        vis[x.u]=true;
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

int main()
{
    while(~scanf("%d", &n))
    {
        init();
        for(int i=2; i<=n; i++)
            for(int j=1; j<i; j++)
            {
                char s[20];
                int dis;
                scanf("%s", s);
                if(s[0]!='x')
                {
                    dis=change(s);
                    AddEdge(i, j, dis);
                    AddEdge(j, i, dis);
                }
            }
        Dijkstra();
        int ans=0;
        for(int i=1; i<=n; i++)
            ans=max(ans, d[i]);
        printf("%d\n", ans);
    }
    return 0;
}
