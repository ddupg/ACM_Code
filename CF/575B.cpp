#include <bits/stdc++.h>
#define clr(a, x) memset(a, x, sizeof a)
using namespace std;

const int maxn=100000+100;
const int mod=1000000007;

struct Edge
{
    int u, v, op;
    int get(int x)
    {
        return x==u?v:u;
    }
} E[maxn];

int n, top[maxn], fa[maxn], dep[maxn], sz[maxn];
int p[maxn], fp[maxn], son[maxn], pos;
vector<int> G[maxn];
int cost[maxn*10];

void init()
{
    pos=0;
    clr(son, 0xff);
    for(int i=0; i<maxn; i++)
        G[i].clear();
    for(int i=1, c=1; i<=1e6; i++, (c<<=1)%=mod)
        cost[i]=(c+cost[i-1])%mod;
}

void dfs(int u, int f, int d)
{
    dep[u]=d, fa[u]=f;
    sz[u]=1;
    for(int i=0; i<G[u].size(); i++)
    {
        int v=E[G[u][i]].get(u);
        if(v==f)continue ;
        dfs(v, u, d+1);
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
        int v=E[G[u][i]].get(u);
        if(v==son[u] || v==fa[u])continue ;
        getpos(v, v);
    }
}

struct Solver
{
    int b[maxn];
    bool was[maxn];
    void add(int u, int v)
    {
        b[p[u]]++, b[p[v]+1]--;
    }
} up, down;

void change(int u, int v)
{
    int f1=top[u], f2=top[v];
    int ans=0;
    while(f1!=f2)
    {
        if(dep[f1]>dep[f2])
        {
            down.add(f1, u);
            u=fa[f1], f1=top[u];
        }
        else
        {
            up.add(f2, v);
            v=fa[f2], f2=top[v];
        }
    }
    if(u==v)return ;
    if(dep[u]<dep[v])
        up.add(son[u], v);
    else
        down.add(son[v], u);
}

int main()
{
    scanf("%d", &n);
    init();
    for(int i=0; i<n-1; i++)
    {
        scanf("%d%d%d", &E[i].u, &E[i].v, &E[i].op);
        G[E[i].u].push_back(i);
        G[E[i].v].push_back(i);
    }
    dfs(1, -1, 0);
    getpos(1, 1);

    for(int i=0; i<n-1; i++)
    {
        int u=E[i].u, v=E[i].v;
        if(!E[i].op)continue ;
        if(fa[u]==v)
            up.was[p[u]]=true;
        else down.was[p[v]]=true;
    }
    int st=1, k;
    scanf("%d", &k);
    while(k--)
    {
        int v;
        scanf("%d", &v);
        change(st, v);
        st=v;
    }
    int ans=0, cnt1=0, cnt2=0;
    for(int i=1; i<=n; i++)
    {
        cnt1+=up.b[i], cnt2+=down.b[i];
        if(up.was[i])ans+=cost[cnt1];
        if(down.was[i])ans+=cost[cnt2];
        if(ans>=mod)ans-=mod;
    }
    printf("%d\n", ans);
    return 0;
}
