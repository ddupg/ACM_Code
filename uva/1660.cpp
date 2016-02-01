#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>
#include <queue>
using namespace std;
const int maxn=200;
const int oo=0x3f3f3f3f;
struct Edge
{
    int u, v, cap, flow;
    Edge(int u=0, int v=0, int c=0, int f=0):u(u), v(v), cap(c), flow(f){}
} e[maxn*maxn];
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
int n, m;

int solve(int t)
{
    net.init(n*2+10);
    for(int i=1; i<n; i++)
        net.AddEdge(i, i+n, 1);
    for(int i=0; i<m; i++)
    {
        net.AddEdge(e[i].u+n, e[i].v, oo);
        net.AddEdge(e[i].v+n, e[i].u, oo);
    }
    return net.Maxflow(n, t);
}

int main()
{
    int u, v;
    while(~scanf("%d%d", &n, &m))
    {
        if(n==0 || n==1)
        {
            printf("%d\n", n);
            continue ;
        }
        for(int i=0; i<m; i++)
        {
            while(getchar()!='(');
            scanf("%d,%d)", &e[i].u, &e[i].v);
        }
        int ans=oo;
        for(int i=1; i<n; i++)
            ans=min(ans, solve(i));
        if(ans==oo)
            ans=n;
        printf("%d\n", ans);
    }
    return 0;
}
