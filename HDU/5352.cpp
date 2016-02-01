#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
#include <vector>
#define clr(a, x) memset(a, x, sizeof a)
#define fst first
#define snd second
#define pb push_back
using namespace std;
typedef pair<int, int> pii;

const int maxn=1010;
const int oo = 0x3f3f3f3f;
struct Edge
{
    int u, v, cap, flow, cost;
    Edge(int u, int v, int cap, int f, int cost):u(u), v(v), cap(cap), flow(f), cost(cost) {}
};
struct MCMF
{
    int n, m, s, t;
    vector<Edge> edge;
    vector<int> G[maxn];
    int inq[maxn], d[maxn], p[maxn], a[maxn];
    void init(int n)
    {
        this->n=n;
        for(int i=0; i<=n; i++)G[i].clear();
        edge.clear();
    }
    void AddEdge(int u, int v, int cap, int cost)
    {
        edge.pb(Edge(u, v, cap, 0, cost));
        edge.pb(Edge(v, u, 0, 0, -cost));
        m=edge.size();
        G[u].pb(m-2);
        G[v].pb(m-1);
    }
    bool SPFA(int s, int t, int& flow, int& cost)
    {
        clr(d, 0x3f);
        clr(inq, 0);
        d[s]=0, inq[s]=1, p[s]=0, a[s]=oo;

        queue<int> q;
        q.push(s);
        while(!q.empty())
        {
            int u=q.front();
            q.pop();
            inq[u]=0;
            for(int i=0; i<G[u].size(); i++)
            {
                Edge& e=edge[G[u][i]];
                if(e.cap>e.flow && d[e.v]>d[u]+e.cost)
                {
                    d[e.v]=d[u]+e.cost;
                    p[e.v]=G[u][i];
                    a[e.v]=min(a[u], e.cap-e.flow);
                    if(!inq[e.v])
                    {
                        q.push(e.v);
                        inq[e.v]=true;
                    }
                }
            }
        }
        if(d[t]==oo)return false;
        flow+=a[t];
        cost+=d[t]*a[t];
        int u=t;
        while(u!=s)
        {
            edge[p[u]].flow+=a[t];
            edge[p[u]^1].flow-=a[t];
            u=edge[p[u]].u;
        }
        return true;
    }
    pii Mincost(int s, int t)
    {
        int flow=0, cost=0;
        while(SPFA(s, t, flow, cost))
            ;
        return pii(flow, cost);
    }
} net;

int g[maxn][maxn];
int fa[maxn];
int n, m, k, tot, kase;

int find(int x)
{
    return fa[x]==x?x:fa[x]=find(fa[x]);
}
void build(int u, int id)
{
    for(int i=1; i<=n; i++)
        fa[i]=i;
    for(int i=1; i<=n; i++)
        for(int j=i+1; j<=n; j++)
            if(g[i][j]==kase)
                fa[find(i)]=find(j);
    for(int i=1, p=find(u); i<=n; i++)
        if(p==find(i))
            net.AddEdge(id+n+1, i, 1, -id);
}
int main()
{
    int TT;
    scanf("%d", &TT);
    for(kase=1; kase<=TT; kase++)
    {
        scanf("%d%d%d", &n, &m, &k);
        int S=0, T=n+1;
        net.init(n+m+10);
        for(int i=1; i<=n; i++)
            net.AddEdge(i, T, 1, 0);
        int cnt=0;
        for(int i=1; i<=m; i++)
        {
            int op, x, y;
            scanf("%d", &op);
            if(op==1)
            {
                scanf("%d", &x);
                build(x, ++cnt);
                net.AddEdge(S, cnt+n+1, k, 0);
            }
            else if(op==2)
            {
                scanf("%d%d", &x, &y);
                g[x][y]=g[y][x]=kase;
            }
            else
            {
                int t, u, v;
                scanf("%d", &t);
                while(t--)
                {
                    scanf("%d%d", &u, &v);
                    g[u][v]=g[v][u]=0;
                }
            }
        }
        printf("%d\n", net.Mincost(S, T).first);
        for(int i=1; i<=cnt; i++)
        {
            int ans=0, u=i+n+1;
            for(int j=0; j<net.G[u].size(); j++)
            {
                Edge& e=net.edge[net.G[u][j]];
                if(e.v==S)
                    ans+=e.flow;
            }
            if(i>1)putchar(' ');
            printf("%d", -ans);
        }
        putchar('\n');
    }
    return 0;
}
