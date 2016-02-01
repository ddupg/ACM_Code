#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
#include <vector>
#define mem(a, val) memset((a), (val), sizeof(a))
using namespace std;
typedef long long LL;
const int maxn=220;
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

    bool spfa(int s, int t, int& flow, LL &cost)
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

    LL MincostMaxflow(int s, int t)
    {
        int flow=0;
        LL cost=0;
        while(spfa(s, t, flow, cost));
        return cost;
    }
} net;

int main()
{
    int n, d, r, a[maxn], b[maxn];
    while(~scanf("%d%d%d", &n, &d, &r) && n)
    {
        net.init(n*2+2);
        int S=0, T=2*n+1;
        for(int i=1; i<=n; i++)
        {
            scanf("%d", a+i);
            net.AddEdge(S, i, 1, 0);
        }
        for(int j=1; j<=n; j++)
        {
            scanf("%d", b+j);
            for(int i=1; i<=n; i++)
                net.AddEdge(i, j+n, 1, r*max(0, a[i]+b[j]-d));
            net.AddEdge(j+n, T, 1, 0);
        }
        printf("%d\n", net.MincostMaxflow(S, T));
    }
    return 0;
}

//#include <cstdio>
//#include <iostream>
//#include <algorithm>
//using namespace std;
//
//int main()
//{
//    int n, d, r, a[105], b[105];
//    while(~scanf("%d%d%d", &n, &d, &r) && n)
//    {
//        long long ans=0;
//        for(int i=0; i<n; i++)
//            scanf("%d", a+i);
//        for(int i=0; i<n; i++)
//            scanf("%d", b+i);
//        sort(a, a+n);
//        sort(b, b+n);
//        for(int i=0; i<n; i++)
//            ans+=r*max(a[i]+b[n-i-1]-d, 0);
//        printf("%lld\n", ans);
//    }
//    return 0;
//}
