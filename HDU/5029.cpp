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

const int maxn=100000+100;

int top[maxn], fa[maxn], deep[maxn], sz[maxn];
int p[maxn], fp[maxn], son[maxn], pos;
int ans[maxn];
int cov[maxn<<2];
vector<int> G[maxn], add[maxn], red[maxn];

void init()
{
    pos=0;
    clr(son, 0xff);
    for(int i=0; i<maxn; i++)
        G[i].clear(), add[i].clear(), red[i].clear();
    clr(cov, 0);
}

void dfs1(int u, int f, int d)
{
    deep[u]=d, fa[u]=f;
    sz[u]=1;
    for(int i=0; i<G[u].size(); i++)
    {
        int v=G[u][i];
        if(v==f)continue ;
        dfs1(v, u, d+1);
        sz[u]+=sz[v];
        if(son[u]==-1 || sz[v]>sz[son[u]])
            son[u]=v;
    }
}

void getpos(int u, int sp)
{
    top[u]=sp;
    p[u]=++pos;
    fp[pos]=u;
    if(son[u]==-1)return ;
    getpos(son[u], sp);
    for(int i=0; i<G[u].size(); i++)
    {
        int v=G[u][i];
        if(v==fa[u] || v==son[u])continue ;
        getpos(v, v);
    }
}

void Change(int u, int v, int val)
{
    int f1=top[u], f2=top[v];
    while(f1!=f2)
    {
        if(deep[f1]<deep[f2])
        {
            swap(f1, f2);
            swap(u, v);
        }
        add[p[f1]].pb(val);
        red[p[u]+1].pb(val);
        u=fa[f1];
        f1=top[u];
    }
    if(deep[u]>deep[v])swap(u, v);
    add[p[u]].pb(val);
    red[p[v]+1].pb(val);
}

void update(int p, int val, int l, int r, int rt)
{
    if(l==r)
    {
        cov[rt]+=val;
        return ;
    }
    int mid=l+r>>1;
    if(p<=mid)update(p, val, lson);
    else update(p, val, rson);
    cov[rt]=max(cov[ls], cov[rs]);
}

int query(int l, int r, int rt)
{
    if(l==r)return l;
    int mid=l+r>>1;
    if(cov[ls]==cov[rt])return query(lson);
    else return query(rson);
}

int main()
{
    int n, m;
    while(~scanf("%d%d", &n, &m) && n+m)
    {
        init();
        for(int i=0; i<n-1; i++)
        {
            int u, v;
            scanf("%d%d", &u, &v);
            G[u].pb(v), G[v].pb(u);
        }
        dfs1(1, -1, 0);
        getpos(1, 1);
        while(m--)
        {
            int u, v, w;
            scanf("%d%d%d", &u, &v, &w);
            Change(u, v, w);
        }
        for(int i=1; i<=n; i++)
        {
            for(int j=0; j<add[i].size(); j++)
                update(add[i][j], 1, 1, 1e5, 1);
            for(int j=0; j<red[i].size(); j++)
                update(red[i][j], -1, 1, 1e5, 1);
            ans[fp[i]]=(cov[1]?query(1, 1e5, 1):0);
        }
        for(int i=1; i<=n; i++)
            printf("%d\n", ans[i]);
    }
    return 0;
}
