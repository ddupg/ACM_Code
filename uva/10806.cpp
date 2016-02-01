#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
#include <vector>
#define mem(a, val) memset((a), (val), sizeof(a))
using namespace std;
typedef long long LL;
const int maxn=210;
const int INF=0x3f3f3f3f;

struct Edge
{
    int u, v, c, f, w;
    Edge(int u, int v, int c, int f, int w):u(u), v(v), c(c), f(f), w(w) {}
};

struct MCMF
{
    int n, m;
    vector<Edge> edge;
    vector<int> G[maxn];
    int d[maxn], p[maxn], a[maxn], inq[maxn];

    void init(int n)
    {
        this->n=n;
        for(int i=0; i<=n; i++)
            G[i].clear();
        edge.clear();
    }

    void AddEdge(int u, int v, int c, int w)
    {
        edge.push_back(Edge(u, v, c, 0, w));
        edge.push_back(Edge(v, u, 0, 0, -w));
        m=edge.size();
        G[u].push_back(m-2);
        G[v].push_back(m-1);
    }

    bool spfa(int s, int t, int& flow, int &cost)
    {
        mem(d, INF);
        mem(inq, 0);
        d[s]=0, inq[s]=1, p[s]=0, a[s]=INF;

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
                if(e.c>e.f && d[e.v]>d[u]+e.w)
                {
                    d[e.v]=d[u]+e.w;
                    p[e.v]=G[u][i];
                    a[e.v]=min(a[u], e.c-e.f);
                    if(!inq[e.v])
                    {
                        q.push(e.v);
                        inq[e.v]=1;
                    }
                }
            }
        }
        if(d[t]==INF)return false;
        flow+=a[t];
        cost+=(LL)a[t]*(LL)d[t];
        for(int u=t; u!=s; u=edge[p[u]].u)
        {
            edge[p[u]].f+=a[t];
            edge[p[u]^1].f-=a[t];
        }
        return true;
    }

    int MincostMaxflow(int s, int t, int& cost)
    {
        int flow=0;
        cost=0;
        while(spfa(s, t, flow, cost));
        return flow;
    }
} net;

int main()
{
    int n, m, u, v, c;
    while(~scanf("%d", &n) && n)
    {
        net.init(n);
        scanf("%d", &m);
        while(m--)
        {
            scanf("%d%d%d", &u, &v, &c);
            net.AddEdge(u, v, 1, c);
            net.AddEdge(v, u, 1, c);
        }
        net.AddEdge(0, 1, 2, 0);
        int cost;
        int ans=net.MincostMaxflow(0, n, cost);
        if(ans<2)
            puts("Back to jail");
        else printf("%d\n", cost);
    }
    return 0;
}
