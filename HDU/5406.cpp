#include <iostream>
#include <cstdio>
#include <cstring>
#include <queue>
#include <algorithm>
#define clr(a, x) memset(a, x, sizeof a)
using namespace std;

const int maxn=2200;
const int oo=0x3f3f3f3f;

struct Edge
{
    int u, v, cap, flow, cost, nxt;
    Edge(int u, int v, int c, int f, int co, int nxt):
        u(u), v(v), cap(c), flow(f), cost(co), nxt(nxt){}
    Edge(){}
};

struct MCMF
{
    int s, t;
    Edge E[maxn*maxn+maxn];
    int H[maxn], tot;
    int inq[maxn], d[maxn], p[maxn], a[maxn];
    void init()
    {
        tot=0;
        clr(H, -1);
    }
    void add(int u, int v, int cap, int cost)
    {
        E[tot]=Edge(u, v, cap, 0, cost, H[u]);
        H[u]=tot++;
        E[tot]=Edge(v, u, 0, 0, -cost, H[v]);
        H[v]=tot++;
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
            for(int i=H[u]; ~i; i=E[i].nxt)
            {
                Edge& e=E[i];
                if(e.cap > e.flow && d[e.v]>d[u]+e.cost)
                {
                    d[e.v]=d[u]+e.cost;
                    p[e.v]=i;
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
        cost+=a[t]*d[t];
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

struct Node
{
    int h, d;
    void read()
    {
        scanf("%d%d", &h, &d);
    }
    bool operator < (const Node& a)const
    {
        return h<a.h || (h==a.h && d>a.d);
    }
} a[maxn];

int main()
{
    int T, n;
    scanf("%d", &T);
    while(T--)
    {
        scanf("%d", &n);
        for(int i=0; i<n; i++)
            a[i].read();
        sort(a, a+n);
        int s=n<<1, ss=s+1, tt=ss+1;
        net.init();
        net.add(ss, s, 2, 0);
        for(int i=0; i<n; i++)
        {
            net.add(s, i, 1, 0);
            net.add(i, i+n, 1, -1);
            net.add(i+n, tt, 1, 0);
            for(int j=i+1, lim=0; j<n; j++)
                if(a[j].d<=a[i].d && lim<a[j].d)
                {
                    net.add(i+n, j, 1, 0);
                    net.add(i, j, 1, 0);
                    lim=a[j].d;
                }
        }
        printf("%d\n", -net.MinCost(ss, tt));
    }
    return 0;
}
