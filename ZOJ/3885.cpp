#include <cstdio>
#include <cmath>
#include <cstring>
#include <algorithm>
#define fst first
#define snd second
using namespace std;
typedef pair<int, int> pii;

const int maxn = 510;
const int maxm = 100010;
const int oo = 0x3f3f3f3f;
struct Edge
{
    int v,cap,flow,cost,next;
    Edge() {}
    Edge(int _v,int _cap,int _cost,int _next) : v(_v),cap(_cap),cost(_cost),next(_next) {}
};
struct ZKW
{
    int S,T,flow,cost,head[maxn],biao[maxn],n,vis[maxn];
    int E;
    Edge edge[maxm];
    void init(int n)
    {
        this->n = n;
        fill(head,head+n,-1);
        E = 0;
    }
    void addedge(int i,int j,int cap,int cost)
    {
        edge[E] = Edge(j,cap,cost,head[i]);
        head[i] = E++;
        edge[E] = Edge(i,0,-cost,head[j]);
        head[j] = E++;
    }
    int aug(int u,int maxCap)
    {
        if(u == T)
        {
            cost += biao[T] * maxCap;
            flow += maxCap;
            return maxCap;
        }
        vis[u] = 1;
        for(int i = head[u]; ~i; i = edge[i].next)
        {
            Edge &go = edge[i];
            if(go.cap-go.flow>0&&!vis[go.v]&&biao[u]+go.cost==biao[go.v])
            {
                if(int d = aug(go.v,min(maxCap,go.cap-go.flow)))
                {
                    go.flow += d;
                    edge[i^1].flow -= d;
                    return d;
                }
            }
        }
        return 0;
    }
    bool update()
    {
        int d = oo;
        for(int i = 0; i < n; i++) if(vis[i])
            {
                for(int j = head[i]; ~j; j = edge[j].next)
                {
                    Edge &go = edge[j];
                    if(go.cap-go.flow>0&&!vis[go.v])
                        d = min(d,biao[i]+go.cost-biao[go.v]);
                }
            }
        if(d == oo) return false;
        for(int i = 0; i < n; i++) if(!vis[i]) biao[i] += d;
        return true;
    }
    pair<int,int> solve(int S,int T)
    {
        this->S = S;
        this->T = T;
        for(int i = 0; i < n; i++) biao[i]=0;
        for(int i = 0; i < E; i++) edge[i].flow = 0;
        flow = 0;
        cost = 0;
        do
        {
            do
            {
                memset(vis,0,sizeof(vis));
            }
            while(aug(S,oo));
        }
        while(update());
        return make_pair(flow,cost);
    }
} net;

int a[maxn], b[maxn];

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
            net.addedge(S, i, a[i], 0);
            net.addedge(i, T, b[i], 0);
        }
        while(m--)
        {
            int x, y;
            scanf("%d%d", &x, &y);
            net.addedge(x, y, oo, 1);
            net.addedge(y, x, oo, 1);
        }
        pii ans=net.solve(S, T);
        if(ans.fst<sum)puts("-1");
        else printf("%d\n", ans.snd);
    }
    return 0;
}
