#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>
#include <queue>
#include <list>
#define clr(a, x) memset(a, x, sizeof a)
#define ALL(a) a.begin(), a.end()
#define pb push_back
using namespace std;
typedef long long LL;

const int maxn=6060;

int n, val[maxn], d[maxn], g[maxn], ans=0;
vector<int> G[maxn];

void dfs(int u, int f)
{
    int k=lower_bound(g+1, g+1+n, val[u])-g;
    d[u]=k;
    int t=g[k];
    g[k]=val[u];
    ans=max(ans, d[u]);
    for(int i=0; i<G[u].size(); i++)
    {
        int v=G[u][i];
        if(v==f)continue ;
        dfs(v, u);
    }
    g[k]=t;
}

int main()
{
    scanf("%d", &n);
    for(int i=1; i<=n; i++)
        scanf("%d", val+i);
    for(int i=0; i<n-1; i++)
    {
        int u, v;
        scanf("%d%d", &u, &v);
        G[u].pb(v);
        G[v].pb(u);
    }
    for(int i=1; i<=n; i++)
    {
        clr(g, 0x3f);
        dfs(i, -1);
    }
    printf("%d\n", ans);
    return 0;
}
