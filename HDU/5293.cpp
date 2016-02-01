#pragma comment(linker, "/STACK:1024000000,1024000000")
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#define clr(a, x) memset(a, x, sizeof a)
#define ALL(a) a.begin(), a.end()
#define fst first
#define snd second
#define pb push_back
#define mp make_pair
using namespace std;
typedef long long LL;
typedef pair<int, int> pii;
typedef pair<pii, int> piii;

const int maxn=100000+100;
const int DEG=20;

inline int scan()
{
    int x=0;
    char c=getchar();
    while(!isdigit(c))c=getchar();
    while(isdigit(c))x=x*10+c-'0', c=getchar();
    return x;
}

struct BIT
{
    int bit[maxn<<1];
    int n;
    void init(int n)
    {
        this->n=n;
        clr(bit, 0);
    }
    void add(int x, int v)
    {
        for(x; x<=n; x+=x&-x)
            bit[x]+=v;
    }
    int qry(int x)
    {
        int ans=0;
        for(; x; x-=x&-x)
            ans+=bit[x];
        return ans;
    }
} D, S;

int n, m;
vector<int> G[maxn];
vector<piii> L[maxn];
int fa[maxn][DEG], deg[maxn];
int l[maxn], r[maxn], idx;
int d[maxn], s[maxn];

void init()
{
    D.init(n<<1);
    S.init(n<<1);
    for(int i=1; i<=n; i++)
        G[i].clear(), L[i].clear();
    idx=0;
}

void dfs(int u)
{
    for(int i=1; i<DEG; i++)
        fa[u][i]=fa[fa[u][i-1]][i-1];
    l[u]=++idx;
    for(int i=0; i<G[u].size(); i++)
    {
        int v=G[u][i];
        if(v==fa[u][0])continue ;
        fa[v][0]=u;
        deg[v]=deg[u]+1;
        dfs(v);
    }
    r[u]=++idx;
}

int par(int u, int det)
{
    for(int i=0; det; det>>=1, i++)
        if(det&1)
            u=fa[u][i];
    return u;
}

int LCA(int u, int v)
{
    if(deg[u]>deg[v])swap(u, v);
    int tu=u, tv=v;
    tv=par(v, deg[v]-deg[u]);
    if(tu==tv)return tu;
    for(int i=DEG-1; i>=0; i--)
    {
        if(fa[tu][i]==fa[tv][i])continue ;
        tu=fa[tu][i], tv=fa[tv][i];
    }
    return fa[tu][0];
}

void dp(int x)
{
    s[x]=d[x]=0;
    for(int i=0; i<G[x].size(); i++)
    {
        int v=G[x][i];
        if(v==fa[x][0])continue ;
        dp(v);
        s[x]+=d[v];
    }
    d[x]=s[x];
    for(int i=0; i<L[x].size(); i++)
    {
        int u=L[x][i].fst.fst, v=L[x][i].fst.snd, w=L[x][i].snd;
        d[x]=max(d[x], w+s[x]+S.qry(l[u])+S.qry(l[v])-D.qry(l[u])-D.qry(l[v]));
    }
    D.add(l[x], d[x]);
    D.add(r[x], -d[x]);
    S.add(l[x], s[x]);
    S.add(r[x], -s[x]);
}

int main()
{
    int T;
    scanf("%d", &T);
    while(T--)
    {
        scanf("%d%d", &n, &m);
        init();
        for(int i=0; i<n-1; i++)
        {
            int u, v;
            scanf("%d%d", &u, &v);
            G[u].pb(v);
            G[v].pb(u);
        }
        deg[1]=0, fa[1][0]=1;
        dfs(1);
        while(m--)
        {
            int u, v, w;
            scanf("%d%d%d", &u, &v, &w);
            L[LCA(u, v)].pb(mp(mp(u, v), w));
        }
        dp(1);
        printf("%d\n", d[1]);
    }
    return 0;
}
