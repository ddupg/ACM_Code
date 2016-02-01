#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>
#include <queue>
#include <cstdio>
using namespace std;
const int maxn=3000;
const int oo=0x3f3f3f3f;

struct Edge
{
    int u, v, cap, flow;
    Edge(int u, int v, int c, int f):u(u), v(v), cap(c), flow(f) {}
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
    int MaxFlow(int s, int t)
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

char g[55][55];
const int dx[]= {0, 0, -1, 1};
const int dy[]= {1, -1, 0, 0};
int n, m, d, f, b;
bool inside(int x, int y)
{
    return x<=n && y<=m && x && y;
}

int main()
{
    int T;
    scanf("%d", &T);
    while(T--)
    {
        scanf("%d%d", &m, &n);
        scanf("%d%d%d", &d, &f, &b);
        for(int i=1; i<=n; i++)
            scanf("%s", g[i]+1);
        int ans=0;
        for(int i=1; i<=n; i++)
        {
            if(g[i][1]=='.')
            {
                ans+=f;
                g[i][1]='#';
            }
            if(g[i][m]=='.')
            {
                ans+=f;
                g[i][m]='#';
            }
        }
        for(int i=1; i<=m; i++)
        {
            if(g[1][i]=='.')
            {
                ans+=f;
                g[1][i]='#';
            }
            if(g[n][i]=='.')
            {
                ans+=f;
                g[n][i]='#';
            }
        }
        net.init(n*m+100);
        int S=0, T=1;
        for(int i=1; i<=n; i++)
            for(int j=1; j<=m; j++)
            {
                for(int k=0; k<4; k++)
                {
                    int x=i+dx[k], y=j+dy[k];
                    if(!inside(x, y))continue ;
                    net.AddEdge(i*m+j, x*m+y, b);
                }
                if(g[i][j]=='#')
                {
                    if(i==1 || i==n || j==1 || j==m)
                        net.AddEdge(S, i*m+j, oo);
                    else net.AddEdge(S, i*m+j, d);
                }
                else
                    net.AddEdge(i*m+j, T, f);
            }
        printf("%d\n", ans+net.MaxFlow(S, T));
    }
    return 0;
}
