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

const LL mod=1e9+7;
const int maxn=2200;

int lim, n, val[maxn], rt;
vector<int> G[maxn];

LL dfs(int u, int f)
{
    LL ans=1;
    for(int i=0; i<G[u].size(); i++)
    {
        int v=G[u][i];
        if(v==f)continue ;
        if((val[v]<val[rt] && val[v]>=val[rt]-lim) || (val[v]==val[rt] && v<rt))
            ans=(ans+ans*dfs(v, u))%mod;
    }
    return ans;
}

int main()
{
    scanf("%d%d", &lim, &n);
    for(int i=1; i<=n; i++)
        scanf("%d", val+i);
    for(int i=0; i<n-1; i++)
    {
        int u, v;
        scanf("%d%d", &u, &v);
        G[u].pb(v);
        G[v].pb(u);
    }
    LL ans=0;
    for(int i=1; i<=n; i++)
    {
        rt=i;
        ans=(ans+dfs(i, -1))%mod;
    }
    cout<<ans<<endl;
    return 0;
}
