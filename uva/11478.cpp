#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <queue>
#include <vector>
#include <cstring>
using namespace std;
const int maxn=550;
const int oo = 1e4+10;

struct Edge
{
    int u, v, d;
    Edge(int u, int v, int d):u(u), v(v), d(d) {}
};

int n, m;
vector<Edge> edge;
vector<int> G[maxn];

void AddEdge(int u, int v, int dis)
{
    G[u].push_back(edge.size());
    edge.push_back(Edge(u, v, dis));
}

bool Spfa()
{
    int d[maxn];
    int cnt[maxn];
    bool vis[maxn];
    queue<int> q;
    for(int i=1; i<=n; i++)
    {
        q.push(i);
        d[i]=0;
        vis[i]=true;
        cnt[i]++;
    }
    while(!q.empty())
    {
        int x=q.front();
        q.pop();
        vis[x]=false;
        for(int i=0; i<G[x].size(); i++)
        {
            Edge& e=edge[G[x][i]];
            if(d[e.v]>d[x]+e.d)
            {
                d[e.v]=d[x]+e.d;
                if(!vis[e.v])
                {
                    vis[e.v]=true;
                    q.push(e.v);
                    if(++cnt[e.v]>=n)
                        return false;
                }
            }
        }
    }
    return true;
}

bool build(int cur)
{
    for(int i=0; i<m; i++)
        edge[i].d-=cur;
    bool ans=Spfa();
    for(int i=0; i<m; i++)
        edge[i].d+=cur;
    return ans;
}

int main()
{
    while(~scanf("%d%d", &n, &m))
    {
        edge.clear();
        for(int i=0; i<=n; i++)
            G[i].clear();
        for(int i=0; i<m; i++)
        {
            int u, v, dis;
            scanf("%d%d%d", &u, &v, &dis);
            AddEdge(u, v, dis);
        }
        if(!build(1))
            puts("No Solution");
        else if(build(oo))
            puts("Infinite");
        else
        {
            int L=1, R=oo;
            while(L<R)
            {
                int mid=(L+R+1)>>1;
                if(build(mid))
                    L=mid;
                else R=mid-1;
            }
            printf("%d\n", L);
        }
    }
    return 0;
}
