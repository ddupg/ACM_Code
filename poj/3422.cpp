#pragma comment(linker, "/STACK:1024000000,1024000000")
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <string>
#include <list>
#include <cstdlib>
#include <queue>
#include <stack>
#include <cmath>
#define ALL(a) a.begin(), a.end()
#define clr(a, x) memset(a, x, sizeof a)
#define fst first
#define snd second
#define pb push_back
#define mp make_pair
#define ls (rt<<1)
#define rs (ls|1)
#define lson l, mid, ls
#define rson mid+1, r, rs
using namespace std;
typedef long long LL;
typedef pair<int, int> pii;

const int maxn=2555<<1;
const int oo=0x3f3f3f3f;
struct Edge
{
    int u, v, cap, flow, cost;
    Edge(int u, int v, int cap, int f, int cost):u(u), v(v), cap(cap), flow(f), cost(cost) {}
};
struct MCMF
{
    int n, m, s, t;
    vector<Edge> E;
    vector<int> G[maxn];
    int inq[maxn], d[maxn], p[maxn], a[maxn];
    void init(int n)
    {
        this->n=n;
        for(int i=0; i<=n; i++)G[i].clear();
        E.clear();
    }
    void add(int u, int v, int cap, int cost)
    {
        E.push_back(Edge(u, v, cap, 0, cost));
        E.push_back(Edge(v, u, 0, 0, -cost));
        m=E.size();
        G[u].push_back(m-2);
        G[v].push_back(m-1);
    }
    bool spfa(int s, int t, int& flow, int& cost)
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
                Edge& e=E[G[u][i]];
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
            E[p[u]].flow+=a[t];
            E[p[u]^1].flow-=a[t];
            u=E[p[u]].u;
        }
        return true;
    }
    pii MinCost(int s, int t)
    {
        int flow=0, cost=0, ans=0;
        while(spfa(s, t, flow, cost))
            ;
        return pii(flow, cost);
    }
} net;

int n, m, g[55][55];

inline int getid(int x, int y)
{
    return (x-1)*n+y;
}

int main()
{
    while(~scanf("%d%d", &n, &m))
    {
        net.init(n*n*2+10);
        int ss=0, s=2*n*n+1, t=2*n*n+2;
        net.add(ss, s, m, 0);
        for(int i=1; i<=n; i++)
            for(int j=1; j<=n; j++)
            {
                scanf("%d", &g[i][j]);
                net.add(s, getid(i, j), 1, 0);
                net.add(n*n+getid(i, j), t, 1, 0);
                net.add(getid(i, j), n*n+getid(i, j), 1, -g[i][j]);
                if(i<n)net.add(n*n+getid(i, j), getid(i+1, j), 1, 0);
                if(j<n)net.add(n*n+getid(i, j), getid(i, j+1), 1, 0);
            }
        printf("%d\n", -net.MinCost(ss, t).snd);
    }
    return 0;
}
