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
using namespace std;
typedef long long LL;
typedef pair<int, int> pii;

const int maxn = 210;
const int maxm = maxn*maxn;
const double oo = 1e9;
const double eps=1e-8;


struct Edge
{
    int u, v, id;
    double cap, flow;
    Edge(int u, int v, double cap, double flow, int id):u(u), v(v), cap(cap), flow(flow), id(id) {}
};

struct Dinic
{
    int n, m, s, t;
    vector<Edge> E;
    vector<int> G[maxn];
    bool vis[maxn];
    int d[maxn], cur[maxn];
    void init(int n)
    {
        this->n=n;
        for(int i=0; i<=n; i++)
            G[i].clear();
        E.clear();
    }
    void add(int u, int v, double cap, int id)
    {
        E.pb(Edge(u, v, cap, 0, id));
        E.pb(Edge(v, u, cap, 0, id));
        m=E.size();
        G[u].pb(m-2);
        G[v].pb(m-1);
    }
    bool bfs()
    {
        clr(vis, 0);
        queue<int> q;
        q.push(s);
        vis[s]=1;
        d[s]=0;
        while(!q.empty())
        {
            int x=q.front();
            q.pop();
            for(int i=0; i<G[x].size(); i++)
            {
                Edge& e=E[G[x][i]];
                if(!vis[e.v] && e.cap-e.flow>eps)
                {
                    vis[e.v]=true;
                    d[e.v]=d[x]+1;
                    q.push(e.v);
                }
            }
        }
        return vis[t];
    }
    double dfs(int x, double a)
    {
        if(x==t || a<eps)return a;
        double flow=0, f;
        for(int& i=cur[x]; i<G[x].size(); i++)
        {
            Edge& e=E[G[x][i]];
            if(d[x]+1==d[e.v] && (f=dfs(e.v, min(a, e.cap-e.flow)))>eps)
            {
                e.flow+=f;
                E[G[x][i]^1].flow-=f;
                flow+=f;
                a-=f;
                if(a<eps)break;
            }
        }
        return flow;
    }
    double MaxFlow(int s, int t)
    {
        this->s=s;
        this->t=t;
        double flow=0;
        while(bfs())
        {
            clr(cur, 0);
            flow+=dfs(s, oo);
        }
        return flow;
    }

} net;

int n, m, x[maxm], y[maxm], w[maxm];

bool build(double lim)
{
    net.init(n);
    double ans=0;
    for(int i=0; i<m; i++)
    {
        int u=x[i], v=y[i];
        double c=w[i]-lim;
        if(c<eps)ans+=c;
        else net.add(u, v, c, i);
    }
    ans+=net.MaxFlow(1, n);
    return ans<=0;
}
int vt[maxm];
void solve(double lim)
{
    int cnt=0;
    for(int i=0; i<m; i++)
        if(w[i]-lim<eps)
            vt[cnt++]=i;
    net.bfs();
    for(int i=1; i<=n; i++)
        if(net.vis[i])
            for(int j=0; j<net.G[i].size(); j++)
            {
                Edge& e=net.E[net.G[i][j]];
                if(!net.vis[e.v] && e.cap-e.flow<eps)
                    vt[cnt++]=e.id;
            }
    printf("%d\n", cnt);
    sort(vt, vt+cnt);
    for(int i=0; i<cnt; i++)
    {
        if(i)putchar(' ');
        printf("%d", vt[i]+1);
    }
    puts("");
}

int main()
{
    while(~scanf("%d%d", &n, &m))
    {
        for(int i=0; i<m; i++)
            scanf("%d%d%d", x+i, y+i, w+i);
        double L=0, R=oo;
        while(R-L>eps)
        {
            double mid=(L+R)/2;
            if(build(mid))R=mid;
            else L=mid;
        }
        solve(L);
    }
    return 0;
}
