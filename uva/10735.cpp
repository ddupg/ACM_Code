#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <queue>
#include <stack>
#include <cstring>
using namespace std;
const int maxn=110;
const int oo=0x3f3f3f3f;

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

struct EDGE
{
    int v, nxt;
};

struct EulerCircle
{
    int n, m;
    bool vis[maxn*5];
    int head[maxn], tot;
    EDGE edge[maxn*5];
    stack<int> S;
    void init(int n, int m)
    {
        this->n=n;
        this->m=m;
        tot=0;
        memset(vis, 0, sizeof vis);
        memset(head, -1, sizeof head);
    }
    void AddEdge(int u, int v)
    {
        edge[tot].v=v;
        edge[tot].nxt=head[u];
        head[u]=tot++;
    }
    void dfs(int u)
    {
        for(int i=head[u]; ~i; i=edge[i].nxt)
            if(!vis[i])
            {
                vis[i]=1;
                dfs(edge[i].v);
            }
        S.push(u);
    }
    void solve()
    {
        dfs(1);
        printf("%d", S.top());
        for(S.pop(); !S.empty(); S.pop())
            printf(" %d", S.top());
        puts("");
    }
} ec;

int main()
{
    int T, n, m, deg[maxn];
    scanf("%d", &T);
    while(T--)
    {
        scanf("%d%d", &n, &m);
        net.init(n+10);
        ec.init(n, m);
        memset(deg, 0, sizeof deg);
        while(m--)
        {
            int u, v;
            char c;
            scanf("%d%d %c", &u, &v, &c);
            deg[u]++, deg[v]--;
            if(c=='U')
                net.AddEdge(u, v, 1);
            else ec.AddEdge(u, v);
        }
        bool ok=true;
        int s=0, t=n+1, sum=0;
        for(int i=1; i<=n; i++)
        {
            if(deg[i]&1)
            {
                ok=false;
                break;
            }
            if(deg[i]>0)
            {
                net.AddEdge(s, i, deg[i]>>1);
                sum+=(deg[i]>>1);
            }
            else net.AddEdge(i, t, -deg[i]>>1);
        }

        if(!ok || net.MaxFlow(s, t)<sum)
            puts("No euler circuit exist");
        else
        {
            for(int i=0; i<net.edge.size(); i+=2)
            {
                Edge& e=net.edge[i];
                if(e.cap>0 && e.u!=s && e.v!=t)
                {
                    if(e.flow==e.cap)
                        ec.AddEdge(e.v, e.u);
                    else ec.AddEdge(e.u, e.v);
                }
            }
            ec.solve();
        }
        if(T)puts("");
    }
    return 0;
}
