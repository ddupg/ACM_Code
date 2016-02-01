#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>
using namespace std;
const int maxn=1100;
const int oo = 0x3f3f3f3f;

struct Edge
{
    int u, v, cap, flow;
    Edge(int u, int v, int c, int f):u(u), v(v), cap(c), flow(f){}
};

struct Dinic
{
    int n, m, s, t;
    vector<Edge> edge;
    vector<int> G[maxn];
    bool vis[maxn];
    int d[maxn];
    int cur[maxn];

    void init(int n)
    {
        this->n=n;
        for(int i=0; i<=n; i++)
            G[i].clear();
        edge.clear();
    }

    void AddEdge(int u, int v, int cap)
    {
        edge.push_back(Edge(u, v, cap, 0));
        edge.push_back(Edge(v, u, 0, 0));
        m=edge.size();
        G[u].push_back(m-2);
        G[v].push_back(m-1);
    }

    bool bfs()
    {
        memset(vis, 0, sizeof vis);
        queue<int> q;
        q.push(s);
        d[s]=0;
        vis[s]=1;
        while(!q.empty())
        {
            int x=q.front();
            q.pop();
            for(int i=0; i<G[x].size(); i++)
            {
                Edge& e=edge[G[x][i]];
                if(!vis[e.v] && e.cap>e.flow)
                {
                    vis[e.v]=true;
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

    int Maxflow(int s, int t)
    {
        this->s=s;
        this->t=t;
        int flow=0;
        while(bfs())
        {
            memset(cur, 0, sizeof cur);
            flow+=dfs(s, oo);
        }
        return flow;
    }
} net;

int main()
{
    int N, F, D;
    while(~scanf("%d%d%d", &N, &F, &D))
    {
        net.init(2*N+F+D+10);
        int S=0, T=2*N+F+D+1;
        for(int i=1; i<=F; i++)
            net.AddEdge(S, i, 1);
        for(int i=1; i<=D; i++)
            net.AddEdge(F+2*N+i, T, 1);
        for(int i=1; i<=N; i++)
            net.AddEdge(F+i, F+N+i, 1);
        for(int i=1; i<=N; i++)
        {
            int x, f, d;
            scanf("%d%d", &f, &d);
            while(f--)
            {
                scanf("%d", &x);
                net.AddEdge(x, F+i, 1);
            }
            while(d--)
            {
                scanf("%d", &x);
                net.AddEdge(N+F+i, F+2*N+x, 1);
            }
        }
        printf("%d\n", net.Maxflow(S, T));
    }
    return 0;
}
