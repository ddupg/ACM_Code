#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <queue>
#include <cmath>
using namespace std;
typedef pair<int, int> pii;
#define fir first
#define sec second
const int maxn=300;
const int oo = 0x3f3f3f3f;

struct Edge
{
    int u, v, cap, flow;
    Edge(int u=0, int v=0, int c=0, int f=0):u(u), v(v), cap(c), flow(f) {}
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

    void AddEdge(int u, int v, int c)
    {
        edge.push_back(Edge(u, v, c, 0));
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


bool dist(int x1, int y1, int x2, int y2, double limit)
{
    return sqrt(1.0*(x1-x2)*(x1-x2)+(y1-y2)*(y1-y2))<=limit;
}

Edge nd[20000+10];

void build(int n, double limit)
{
    net.init(n*2+10);
    for(int i=1; i<=n; i++)
    {
        if(nd[i].cap)net.AddEdge(0, i, nd[i].cap);
        if(nd[i].flow)net.AddEdge(i, i+n, nd[i].flow);
        for(int j=1; j<i; j++)
        {
            if(dist(nd[i].u, nd[i].v, nd[j].u, nd[j].v, limit))
            {
                net.AddEdge(j+n, i, oo);
                net.AddEdge(i+n, j, oo);
            }
        }
    }
}

int main()
{
    int T, n;
    double limit;
    scanf("%d", &T);
    while(T--)
    {
        scanf("%d%lf", &n, &limit);
        int sum=0;
        for(int i=1; i<=n; i++)
        {
            int x, y, c1, c2;
            scanf("%d%d%d%d", &x, &y, &c1, &c2);
            sum+=c1;
            nd[i]=Edge(x, y, c1, c2);
        }
        bool ok=false;
        for(int i=1; i<=n; i++)
        {
            build(n, limit);
            if(net.Maxflow(0, i)==sum)
            {
                if(ok)putchar(' ');
                printf("%d", i-1);
                ok=true;
            }
        }
        if(!ok)printf("-1");
        puts("");
    }
    return 0;
}
