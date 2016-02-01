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
#define ls (rt<<1)
#define rs (ls|1)
#define lson l, mid, ls
#define rson mid+1, r, rs
#define sqr(x) ((x)*(x))
using namespace std;
typedef long long LL;
typedef pair<int, int> pii;

const int maxn=150;
const int maxm=maxn*maxn;
const double oo=1e15;
const double eps=1e-9;

struct Edge
{
    int v, nxt;
    double c;
} ;

struct Dinic
{
    Edge e[maxm<<1];
    int SS, TT, idx, head[maxn];
    int dis[maxn];
    bool vis[maxn];
    bool used[maxm];
    queue<int>q;

    void init(int s, int t)
    {
        SS=s, TT=t;
        idx = 0;
        clr(head, 0xff);
    }

    void add(int u, int v, double c)
    {
        e[idx].v = v, e[idx].c = c;
        e[idx].nxt = head[u];
        head[u] = idx++;

        e[idx].v = u, e[idx].c = 0;
        e[idx].nxt = head[v];
        head[v] = idx++;
    }

    bool bfs()
    {
        clr(dis, 0xff);
        clr(vis, 0);
        dis[SS] = 0, vis[SS] = 1;
        q.push(SS);
        while (!q.empty())
        {
            int u = q.front();
            q.pop();
            vis[u] = 0;
            for (int i = head[u]; ~i; i = e[i].nxt)
            {
                int v = e[i].v;
                double c = e[i].c;
                if (dis[v] == -1 && c>eps)
                {
                    dis[v] = dis[u] + 1;
                    if (!vis[v])
                    {
                        vis[v] = 1;
                        q.push(v);
                    }
                }
            }
        }
        return dis[TT] != -1;
    }

    double dfs(int u, double flow)
    {
        if (u == TT) return flow;
        double tf = 0, f;
        for (int i = head[u]; ~i; i = e[i].nxt)
        {
            int v = e[i].v;
            double c = e[i].c;
            if (dis[u]+1 == dis[v] && c>eps && (f = dfs(v, min(flow-tf, c)))>eps)
            {
                e[i].c -= f, e[i^1].c += f;
                tf += f;
                if (tf == flow) return tf;
            }
        }
        if (!tf) dis[u] = -1;
        return tf;
    }

    double dinic()
    {
        double flow=0;
        while (bfs())
            flow+=dfs(SS, oo);
        return flow;
    }
} net;

double A[maxn>>1], B[maxn>>1];
int n, m, g[maxn>>1][maxn>>1];

bool judge(double lim)
{
    int S=0, T=n+m+3;
    double sum=0;
    net.init(S, T);
    for(int i=1; i<=m; i++)
        net.add(S, i, lim*B[i]);
    for(int i=1; i<=n; i++)
    {
        net.add(i+m, T, A[i]);
        sum+=A[i];
    }
    for(int i=1; i<=m; i++)
        for(int j=1; j<=n; j++)
            if(g[i][j])
                net.add(i, j+m, oo);
    return sum-net.dinic()<eps;
}

int main()
{
    while(~scanf("%d%d", &n, &m))
    {
        for(int i=1; i<=n; i++)
            scanf("%lf", A+i);
        for(int i=1; i<=m; i++)
            scanf("%lf", B+i);
        for(int i=1; i<=m; i++)
            for(int j=1; j<=n; j++)
                scanf("%d", &g[i][j]);
        double L=0, R=1e5;
        while(R-L>eps)
        {
            double mid=(R+L)*0.5;
            if(judge(mid)) R=mid;
            else L=mid;
        }
        printf("%.10f\n", L);
    }
    return 0;
}
