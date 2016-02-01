#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;
typedef long long LL;

const int maxn=1010;
const LL mod=1e9+7;

int n, sz[maxn];
LL inv[maxn], base[maxn], d[maxn][maxn];
vector<int> G[maxn];

LL Pow(LL x, LL b)
{
    LL ans=1;
    for(; b; b>>=1)
    {
        if(b&1)ans=ans*x%mod;
        x=x*x%mod;
    }
    return ans;
}

void init()
{
    base[0]=1;
    for(int i=1; i<maxn; i++)
    {
        inv[i]=Pow(i, mod-2);
        base[i]=base[i-1]*i%mod;
    }
}

void dfs(int u, int f)
{
    sz[u]=1;
    for(int i=0; i<G[u].size(); i++)
    {
        int v=G[u][i];
        if(v==f)continue ;
        dfs(v, u);
        sz[u]+=sz[v];
    }
}

int main()
{
    init();
    int T, k, kase=0;
    scanf("%d", &T);
    while(T--)
    {
        scanf("%d%d", &n, &k);
        for(int i=1; i<=n; i++)
            G[i].clear();
        for(int i=0; i<n-1; i++)
        {
            int u, v;
            scanf("%d%d", &u, &v);
            G[u].push_back(v);
            G[v].push_back(u);
        }
        dfs(1, -1);
        d[0][0]=1;
        for(int i=1; i<=n; i++)
            for(int j=0; j<=i; j++)
            {
                d[i][j]=0;
                if(j)d[i][j]+=d[i-1][j-1]*inv[sz[i]]%mod;
                d[i][j]+=d[i-1][j]*(sz[i]-1)%mod*inv[sz[i]]%mod;
                d[i][j]%=mod;
            }
        LL ans=d[n][k]*base[n]%mod;
        printf("Case #%d: %I64d\n", ++kase, ans);
    }
    return 0;
}
