#include <iostream>
#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;
const int maxn=1100;
const int oo=0x3f3f3f3f;

struct Edge
{
    int u, v, d;
    Edge(int u, int v, int d):u(u), v(v), d(d){};
};

int n, ml, md, d[maxn];
vector<int> G[maxn];
vector<Edge> edge;
bool vis[maxn];

void init()
{
    for(int i=1; i<=n; i++)
        G[i].clear();
    edge.clear();
    memset(d, 0x3f, sizeof d);
}

void AddEdge(int u, int v, int dis)
{
    G[u].push_back(edge.size());
    edge.push_back(Edge(u, v, dis));
}

int spfa()
{
    int cnt[maxn]={0};
    queue<int> q;
    q.push(1);
    vis[1]=true;
    d[1]=0;
    cnt[1]++;
    while(!q.empty())
    {
        int x=q.front();
        q.pop();
        if(cnt[x]>=n)return -1;
        vis[x]=false;
        for(int i=0; i<G[x].size(); i++)
        {
            Edge& e=edge[G[x][i]];
            if(d[e.v]>d[e.u]+e.d)
            {
                d[e.v]=d[e.u]+e.d;
                if(!vis[e.v])
                {
                    q.push(e.v);
                    cnt[e.v]++;
                    vis[e.v]=true;
                }
            }
        }
    }
    return d[n];
}

int main()
{
    while(~scanf("%d%d%d", &n, &ml, &md))
    {
        init();
        int u, v, dis;
        while(ml--)
        {
            scanf("%d%d%d", &u, &v, &dis);
            if(u>v)swap(u, v);
            AddEdge(u, v, dis);
        }
        while(md--)
        {
            scanf("%d%d%d", &u, &v, &dis);
            if(u>v)swap(u, v);
            AddEdge(v, u, -dis);
        }
        int ans=spfa();
        printf("%d\n", ans==oo?-2:ans);
    }
    return 0;
}
