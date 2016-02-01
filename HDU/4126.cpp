#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#define clr(a, x) memset(a, x, sizeof a)
#define ls (rt<<1)
#define rs (ls|1)
#define lson l, mid, ls
#define rson mid+1, r, rs
using namespace std;
typedef long long LL;

const int maxn=3030;

struct Edge
{
    int u, v, w;
    Edge(){}
    Edge(int u, int v, int w):u(u), v(v), w(w){}
    bool operator < (const Edge e)const
    {
        return w<e.w;
    }
} edge[maxn*maxn];

int n, m, pre[maxn], deg[maxn], fa[maxn], wei[maxn];
double cost;
vector<Edge> G[maxn];
int tot, num[maxn], son[maxn];
int p[maxn], fp[maxn], pos, top[maxn];

void init()
{
    for(int i=1; i<=n; i++)
    {
        pre[i]=i;
        G[i].clear();
    }
    cost=0;
    pos=0;
}

int find(int x)
{
    return pre[x]==x?x:pre[x]=find(pre[x]);
}

void Prime()
{
    sort(edge, edge+m);
    for(int i=0, cnt=0; i<m, cnt<n-1; i++)
    {
        int u=edge[i].u, v=edge[i].v, w=edge[i].w;
        if(find(u)==find(v))continue ;
        cost+=w;
        pre[pre[u]]=pre[v];
        G[u].push_back(Edge(u, v, w));
        G[v].push_back(Edge(v, u, w));
        ++cnt;
    }
}

void build(int u, int f, int d)
{
    deg[u]=d, fa[u]=f, num[u]=1, son[u]=-1;
    for(int i=0; i<G[u].size(); i++)
    {
        Edge& e=G[u][i];
        if(e.v==f)continue ;
        wei[e.v]=e.w;
        build(e.v, u, d+1);
        num[u]+=num[e.v];
        if(son[u]==-1 || num[e.v]>num[son[u]])
            son[u]=e.v;
    }
}

void dfs(int u, int sp)
{
    top[u]=sp;
    p[u]=++pos;
    fp[pos]=u;
    if(son[u]==-1)return ;
    dfs(son[u], sp);
    for(int i=0; i<G[u].size(); i++)
    {
        Edge& e=G[u][i];
        if(e.v!=son[u] && e.v!=fa[u])
            dfs(e.v, e.v);
    }
}

int cov[maxn<<2];

void pushdown(int rt)
{
    cov[ls]=min(cov[ls], cov[rt]);
    cov[rs]=min(cov[rs], cov[rt]);
}

void update(int L, int R, int val, int l, int r, int rt)
{
    if(L<=l && R>=r)
    {
        cov[rt]=min(cov[rt], val);
        return ;
    }
    pushdown(rt);
    int mid=l+r>>1;
    if(L<=mid)update(L, R, val, lson);
    if(R>mid) update(L, R, val, rson);
}

int query(int p, int l, int r, int rt)
{
    if(l==r)return cov[rt];
    pushdown(rt);
    int mid=l+r>>1;
    if(p<=mid)return query(p, lson);
    else return query(p, rson);
}

void Update(int u, int v, int val)
{
    int f1=top[u], f2=top[v];
    while(f1!=f2)
    {
        if(deg[f1]<deg[f2])
            swap(f1, f2), swap(u, v);
        update(p[f1], p[u], val, 1, pos, 1);
        u=fa[f1], f1=top[u];
    }
    if(u==v)return ;
    if(deg[u]>deg[v])swap(u, v);
    update(p[son[u]], p[v], val, 1, pos, 1);
}

int main()
{
    while(~scanf("%d%d", &n ,&m) && n+m)
    {
        init();
        for(int i=0; i<m; i++)
        {
            scanf("%d%d%d", &edge[i].u, &edge[i].v, &edge[i].w);
            ++edge[i].u, ++edge[i].v;
        }
        Prime();
        build(1, -1, 0);
        dfs(1, 1);
        clr(cov, 0x3f);
        for(int i=0; i<m; i++)
        {
            int u=edge[i].u, v=edge[i].v;
            if(deg[u]>deg[v])swap(u, v);
            if(fa[v]==u)continue ;
            Update(u, v, edge[i].w);
        }
        int q;
        scanf("%d", &q);
        double ans=0;
        for(int i=0; i<q; i++)
        {
            int u, v, w;
            scanf("%d%d%d", &u, &v, &w);
            ++u, ++v;
            if(deg[u]>deg[v])swap(u, v);
            if(fa[v]!=u) ans+=cost;
            else ans+=cost-wei[v]+min(query(p[v], 1, pos, 1), w);
        }
        printf("%.4f\n", ans/q);
    }
    return 0;
}
