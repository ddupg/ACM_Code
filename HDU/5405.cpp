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

const int maxn=100000+100;
const LL mod=1e9+7;

int fa[maxn], dep[maxn], sz[maxn], top[maxn], L[maxn], R[maxn];
int son[maxn], pos;
int val[maxn];
LL sum, s[maxn];
vector<int> G[maxn];

LL sqr(LL x)
{
    x%=mod;
    return x*x%mod;
}

void init()
{
    pos=0;
    sum=0;
    for(int i=0; i<maxn; i++)
        G[i].clear();
    clr(son, -1);
}

struct BIT
{
    int n;
    LL c[maxn];
    void init(int _n)
    {
        n=_n;
        clr(c, 0);
    }
    void build()
    {
        for(int i=1; i<=n; i++)
        {
            int x=i+(i&-i);
            if(x<=n)c[x]=c[x]+c[i];
            c[i]%=mod;
        }
    }
    void add(int x, LL v)
    {
        for(; x<=n; x+=x&-x)
            c[x]=(c[x]+v)%mod;
    }
    LL qry(int x)
    {
        LL ans=0;
        for(; x; x-=x&-x)
            ans+=c[x];
        return ans%mod;
    }
} CW, CP;

void dfs1(int u, int f, int d)
{
    dep[u]=d;
    fa[u]=f;
    sz[u]=1;
    for(int i=0; i<G[u].size(); i++)
    {
        int v=G[u][i];
        if(v==f)continue ;
        dfs1(v, u, d+1);
        sz[u]+=sz[v];
        if(son[u]==-1 || sz[son[u]]<sz[v])
            son[u]=v;
    }
}

void getpos(int u, int sp)
{
    top[u]=sp;
    L[u]=++pos;

    s[u]=val[u];
    CW.c[L[u]]=val[u];
    if(~son[u]) getpos(son[u], sp), s[u]+=s[son[u]];
    LL ss=0;
    for(int i=0; i<G[u].size(); i++)
    {
        int v=G[u][i];
        if(v==fa[u] || v==son[u])continue ;
        getpos(v, v);
        s[u]+=s[v];
        ss=(ss+sqr(s[v]))%mod;
    }
    R[u]=pos;
    CP.c[L[u]]=ss;
}

inline LL qryw(int u)
{
    return CW.qry(R[u])-CW.qry(L[u]-1);
}

void change(int u, int x)
{
    CW.add(L[u], x);
    (sum+=x)%=mod;
    val[u]+=x;
    u=top[u];
    while(fa[u])
    {
        LL s=qryw(u);
        CP.add(L[fa[u]], sqr(s)-sqr(s-x));
        u=top[fa[u]];
    }
}

LL query(int u, int v)
{
    LL ans=0;
    while(true)
    {
        if(top[u]==top[v])
        {
            if(dep[u]<dep[v])swap(u, v);
            ans+=CP.qry(L[u])-CP.qry(L[v]-1);
            if(~son[u])ans+=sqr(qryw(son[u]));
            ans+=sqr(sum-qryw(v));
            break;
        }
        else
        {
            if(dep[top[u]]<dep[top[v]])swap(u, v);
            ans+=CP.qry(L[u])-CP.qry(L[top[u]]-1);
            if(~son[u])ans+=sqr(qryw(son[u]));
            ans-=sqr(qryw(top[u]));
            u=fa[top[u]];
        }
    }
    return ans%mod;
}

int main()
{
    int n, m;
    while(~scanf("%d%d", &n, &m))
    {
        init();
        CW.init(n);
        CP.init(n);
        for(int i=1; i<=n; i++)
        {
            scanf("%d", val+i);
            sum+=val[i];
        }
        sum%=mod;
        for(int i=0; i<n-1; i++)
        {
            int u, v;
            scanf("%d%d", &u, &v);
            G[u].pb(v);
            G[v].pb(u);
        }
        dfs1(1, 0, 0);
        getpos(1, 1);
        CW.build();
        CP.build();
        while(m--)
        {
            int op, u, v;
            scanf("%d%d%d", &op, &u, &v);
            if(op==1)
            {
                change(u, v-val[u]);
            }
            else
            {
                LL ans=(sqr(sum)-query(u, v))%mod;
                if(ans<0)ans+=mod;
                printf("%I64d\n", ans);
            }
        }
    }
    return 0;
}
