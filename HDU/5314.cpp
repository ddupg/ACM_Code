#pragma comment(linker, "/STACK:102400000,102400000")
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <vector>
#include <algorithm>
#define clr(a, x) memset(a, x, sizeof a)
#define ALL(a) a.begin(), a.end()
#define fst first
#define snd second
#define lowbit(x) ((x)&(-x))
using namespace std;
typedef long long LL;
typedef pair<int, int> pii;

const int maxn=100000+100;

struct BIT
{
    int n, bit[maxn];
    void init(int n_)
    {
        n=n_;
        for(int i=0; i<=n; i++)
            bit[i]=0;
    }
    void add(int x, int v)
    {
        for(; x<=n; x+=lowbit(x))
            bit[x]+=v;
    }
    int sum(int x)
    {
        int ans=0;
        for(; x; x-=lowbit(x))
            ans+=bit[x];
        return ans;
    }
} bit;

int n, dif, sz[maxn], num[maxn];
int rt, tot_size, top;
bool vis[maxn];
pii S[maxn];
int VS[maxn<<1], val[maxn];
LL ans;
vector<int> G[maxn];

void init()
{
    ans=0;
    for(int i=0; i<=n; i++)
    {
        G[i].clear();
        vis[i]=0;
    }
}

void GetRoot(int u, int fa)
{
    sz[u]=1;
    num[u]=0;
    for(int i=0; i<G[u].size(); i++)
    {
        int v=G[u][i];
        if(vis[v] || v==fa)continue ;
        GetRoot(v, u);
        sz[u]+=sz[v];
        num[u]=max(num[u], sz[v]);
    }
    num[u]=max(num[u], tot_size-sz[u]);
    if(rt==-1 || num[u]<num[rt])
        rt=u;
}

void GetLink(int u, int fa, int Min, int Max)
{
    if(Max-Min>dif)return ;
    S[top++]=pii(Min, Max);
    VS[top]=Max;
    sz[u]=1;
    for(int i=0; i<G[u].size(); i++)
    {
        int v=G[u][i];
        if(vis[v] || v==fa)continue ;
        GetLink(v, u, min(Min, val[v]), max(Max, val[v]));
        sz[u]+=sz[v];
    }
}

LL GetNum(int u, int Min, int Max)
{
    top=0;
    GetLink(u, -1, Min, Max);
    sort(S, S+top);

    sort(VS+1, VS+top+1);
    int cnt=unique(VS+1, VS+top+1)-VS-1;

    bit.init(cnt);
    LL ans=0;
    for(int i=top-1; i>=0; i--)
    {
        int R=upper_bound(VS+1, VS+cnt+1, S[i].fst+dif)-VS-1;
        ans+=bit.sum(R);
        bit.add(lower_bound(VS+1, VS+cnt+1, S[i].snd)-VS, 1);
    }
    return ans;
}

void dfs(int u)
{
    vis[u]=1;
    LL tmp=GetNum(u, val[u], val[u]);
    ans+=tmp;
    for(int i=0; i<G[u].size(); i++)
    {
        int v=G[u][i];
        if(vis[v])continue ;
        LL tmp=GetNum(v, min(val[u], val[v]), max(val[u], val[v]));
        ans-=tmp;
        tot_size=sz[v];
        rt=-1;
        GetRoot(v, -1);
        dfs(rt);
    }
}

int main()
{
    int T;
    scanf("%d", &T);
    while(T--)
    {
        scanf("%d%d", &n, &dif);
        init();
        for(int i=1; i<=n; i++)
            scanf("%d", val+i);
        for(int i=0; i<n-1; i++)
        {
            int u, v;
            scanf("%d%d", &u, &v);
            G[u].push_back(v);
            G[v].push_back(u);
        }
        rt=-1, tot_size=n;
        GetRoot(1, -1);
        dfs(rt);
        printf("%I64d\n", ans+ans);
    }
    return 0;
}

/**
1
15 10000
1000000000 456415545 241 45 489 23 4656 45 1 234 456 1000000000 1 0 0
1 2
1 3
1 4
3 5
3 6
6 7
6 8
5 14
5 15
8 9
8 10
8 11
8 12
8 13
**/

