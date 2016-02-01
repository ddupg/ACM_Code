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

const int maxn=455;
const int oo=0x3f3f3f3f;

struct Edge
{
    int u, v, cap, flow, cost;
    Edge(int u, int v, int cap, int f, int cost):u(u), v(v), cap(cap), flow(f), cost(cost){}
};

struct MCMF
{
    int n, m, s, t;
    vector<Edge> E;
    vector<int> G[maxn];
    int inq[maxn], d[maxn], p[maxn], a[maxn];
    void init(int _n)
    {
        n=_n;
        for(int i=0; i<=n; i++)G[i].clear();
        E.clear();
    }
    void add(int u, int v, int cap, int cost)
    {
        E.pb(Edge(u, v, cap, 0, cost));
        E.pb(Edge(v, u, 0, 0, -cost));
        m=E.size();
        G[u].pb(m-2);
        G[v].pb(m-1);
    }
    bool spfa(int s, int t, int& flow, int& cost)
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
        int flow=0, cost=0;
        while(spfa(s, t, flow, cost));
        return pii(flow, cost);
    }

} net;

int main()
{
    int T, u[maxn], v[maxn], w[maxn];
    vector<int> a;
    scanf("%d", &T);
    while(T--)
    {
        int n, lim;
        scanf("%d%d", &n, &lim);
        a.clear();
        for(int i=0; i<n; i++)
        {
            scanf("%d%d%d", u+i, v+i, w+i);
            a.pb(u[i]), a.pb(v[i]);
        }
        sort(ALL(a));
        a.erase(unique(ALL(a)));
        int s=0, t=a.size()+1;
        net.init(a.size()+10);
        for(int i=1; i<=t; i++)
            net.add(i-1, i, lim, 0);
        for(int i=0; i<n; i++)
        {
            int x=lower_bound(ALL(a), u[i])-a.begin()+1;
            int y=lower_bound(ALL(a), v[i])-a.begin()+1;
            net.add(x, y, 1, -w[i]);
        }
        pii ans=net.MinCost(s, t);
        cout<<-ans.snd<<endl;
    }
    return 0;
}
