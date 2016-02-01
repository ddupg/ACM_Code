#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <list>
#include <queue>
#include <stack>
#include <cmath>
#define clr(a, x) memset(a, x, sizeof a)
#define ALL(a) a.begin(), a.end()
#define ls (rt<<1)
#define rs (ls|1)
#define lson l, mid, ls
#define rson mid+1, r, rs
#define fst first
#define snd second
using namespace std;
typedef long long LL;
typedef pair<int, int> pii;

const int oo = 0x3f3f3f3f;
const int maxn=220;

int g[maxn][maxn];
int a[maxn], b[maxn];

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
        edge.push_back(Edge(u, v, cap, 0, cost));
        edge.push_back(Edge(v, u, 0, 0, -cost));
        m=edge.size();
        G[u].push_back(m-2);
        G[v].push_back(m-1);
    }
    bool SPFA(int s, int t, int& flow, int& cost)
    {
        memset(d, 0x3f, sizeof d);
        memset(inq, 0, sizeof inq);
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

int main()
{
    int n, m;
    while(~scanf("%d%d", &n, &m))
    {
        net.init(n*2+10);
        int S=0, T=2*n+1, sum=0;
        for(int i=1; i<=n; i++)
        {
            scanf("%d%d", a+i, b+i);
            sum+=b[i];
        }
        for(int i=1; i<=n; i++)
        {
            net.AddEdge(S, i, a[i], 0);
            net.AddEdge(i, T, b[i], 0);
        }
        while(m--)
        {
            int x, y;
            scanf("%d%d", &x, &y);
            net.AddEdge(x, y, oo, 1);
            net.AddEdge(y, x, oo, 1);
        }
        pii ans=net.Mincost(S, T);
        if(ans.fst<sum)puts("-1");
        else printf("%d\n", ans.snd);
    }
    return 0;
}
