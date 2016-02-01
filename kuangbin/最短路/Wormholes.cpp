#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;
const int maxn=520;
const int oo=1e9;

struct Edge
{
    int u, v, d;
    Edge(int u, int v, int d):u(u), v(v), d(d) {}
};
vector<Edge> edge;
int n, m, w, cnt[maxn], d[maxn];
bool incircle[maxn];
vector<int> G[maxn];

void init()
{
    for(int i=1; i<=n; i++)
        G[i].clear();
    memset(cnt, 0, sizeof(cnt));
    memset(d, 0, sizeof(d));
    edge.clear();
}

bool spfa(int S)
{
    queue<int> q;
    bool vis[maxn]= {0};
    q.push(S);
    vis[S]=true;
    cnt[S]=1;
    for(int i=1; i<=n; i++)
        d[i]=i==S?0:oo;
    while(!q.empty())
    {
        int u=q.front();
        q.pop();
        vis[u]=false;
        if(cnt[u]>n+1)
        {
            incircle[u]=true;
            return true;
        }
        for(int i=0; i<G[u].size(); i++)
        {
            Edge & e=edge[G[u][i]];
            if(d[e.v]>d[u]+e.d)
            {
                d[e.v]=d[u]+e.d;
                if(!vis[e.v])
                {
                    q.push(e.v);
                    vis[e.v]=true;
                    cnt[e.v]++;
                }
            }
        }
    }
    return false;
}

int main()
{
    int T;
    scanf("%d", &T);
    while(T--)
    {
        scanf("%d%d%d", &n, &m, &w);
        init();
        while(m--)
        {
            int u, v, dis;
            scanf("%d%d%d", &u, &v, &dis);
            G[u].push_back(edge.size());
            edge.push_back(Edge(u, v, dis));
            G[v].push_back(edge.size());
            edge.push_back(Edge(v, u, dis));
        }
        while(w--)
        {
            int u, v, dis;
            scanf("%d%d%d", &u, &v, &dis);
            G[u].push_back(edge.size());
            edge.push_back(Edge(u, v, -dis));
        }
        int flag=0;
        for(int i=1; i<=n; i++)
            if(!cnt[i])
                if(flag=spfa(i))
                    break;
        puts(flag?"YES":"NO");
    }
    return 0;
}
