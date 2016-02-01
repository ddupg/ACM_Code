#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>
#include <queue>
#define clr(a, x) memset(a, x, sizeof a)
using namespace std;
const int maxn=420;
const int oo=0x3f3f3f3f;

struct Edge
{
    int u, v, cap, flow;
    Edge(int u, int v, int c, int f):u(u), v(v), cap(c), flow(f) {}
};

struct Dinic
{
    int n, m, s, t, d[maxn], cur[maxn];
    bool vis[maxn];
    vector<Edge> edge;
    vector<int> G[maxn];
    void init(int n)
    {
        this->n=n;
        for(int i=0; i<=n; i++)
            G[i].clear();
        edge.clear();
    }
    int AddEdge(int u, int v, int c)
    {
        edge.push_back(Edge(u, v, c, 0));
        edge.push_back(Edge(v, u, 0, 0));
        m=edge.size();
        G[u].push_back(m-2);
        G[v].push_back(m-1);
        return m-2;
    }
    bool bfs()
    {
        clr(vis, 0);
        queue<int> q;
        q.push(s);
        d[s]=0, vis[s]=1;
        while(!q.empty())
        {
            int x=q.front();
            q.pop();
            for(int i=0; i<G[x].size(); i++)
            {
                Edge& e=edge[G[x][i]];
                if(!vis[e.v] && e.cap>e.flow)
                {
                    vis[e.v]=1;
                    d[e.v]=d[x]+1;
                    q.push(e.v);
                }
            }
        }
        return vis[t];
    }
    int dfs(int x, int a)
    {
        if(x==t || a==0)return a;
        int flow=0, f;
        for(int& i=cur[x]; i<G[x].size(); i++)
        {
            Edge& e=edge[G[x][i]];
            if(d[x]+1==d[e.v] && (f=dfs(e.v, min(a, e.cap-e.flow)))>0)
            {
                e.flow+=f;
                edge[G[x][i]^1].flow-=f;
                flow+=f;
                a-=f;
                if(a==0)break;
            }
        }
        return flow;
    }
    int MaxFlow(int s, int t)
    {
        this->s=s;
        this->t=t;
        int flow=0;
        while(bfs())
        {
            clr(cur, 0);
            flow+=dfs(s, oo);
        }
        return flow;
    }
} net;

int main()
{
    int T, kase=0, n, m, f[230];
    scanf("%d", &T);
    while(T--)
    {
        scanf("%d%d", &n, &m);
        net.init(n+10);
        clr(f, 0);
        while(m--)
        {
            int u, v, D, B;
            scanf("%d%d%d%d", &u, &v, &D, &B);
            net.AddEdge(u, v, B);
            f[u]-=D, f[v]+=D;
        }
        int sum=0;
        for(int i=1; i<=n; i++)
        {
            if(f[i]>0)
            {
                sum+=f[i];
                net.AddEdge(0, i, f[i]);
            }
            else net.AddEdge(i, n+1, -f[i]);
        }
        if(sum==net.MaxFlow(0, n+1))
            printf("Case #%d: happy\n", ++kase);
        else printf("Case #%d: unhappy\n", ++kase);
    }
    return 0;
}
