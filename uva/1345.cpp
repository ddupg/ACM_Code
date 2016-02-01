#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;
const int maxn=2100;
const int oo = 0x3f3f3f3f;

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
vector<pair<int, int> > e;
char s[100000];

bool build(int x)
{
    net.init(n+m+1);
    for(int i=1; i<=n; i++)
        net.AddEdge(0, i, 1);
    for(int i=1; i<=m; i++)
        net.AddEdge(i+n, n+m+1, x);
    for(int i=0; i<e.size(); i++)
        net.AddEdge(e[i].first, e[i].second, 1);
    return n==net.Maxflow(0, n+m+1);
}

int main()
{
    while(~scanf("%d%d", &n, &m) && n+m)
    {
        e.clear();
        gets(s);
        for(int i=1; i<=n; i++)
        {
            gets(s);
            int x=0, flag=0;
            for(int j=0; ; j++)
            {
                if(isdigit(s[j]))
                {
                    x=x*10+s[j]-'0';
                    flag=1;
                }
                else
                {
                    if(flag)
                        e.push_back(make_pair(i, x+n+1));
                    x=flag=0;
                }
                if(!s[j])break;
            }
        }
        int L=0, R=n;
        while(L<R)
        {
            int mid=(L+R)>>1;
            if(build(mid))
                R=mid;
            else L=mid+1;
        }
        printf("%d\n", R);
    }
    return 0;
}
