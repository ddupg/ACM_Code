#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#define clr(a, x) memset(a, x, sizeof a)
#define pb push_back
#define fst first
#define snd second
using namespace std;

const int maxn = 100100;

bool check[maxn+10];
int prime[maxn+10], mu[maxn+10];
void Moblus()
{
    clr(check, 0);
    mu[1] = 1;
    int tot = 0;
    for(int i = 2; i <= maxn; i++)
    {
        if( !check[i] )
        {
            prime[tot++] = i;
            mu[i] = -1;
        }
        for(int j = 0; j < tot; j++)
        {
            if(i * prime[j] > maxn) break;
            check[i * prime[j]] = true;
            if( i % prime[j] == 0)
            {
                mu[i * prime[j]] = 0;
                break;
            }
            else
            {
                mu[i * prime[j]] = -mu[i];
            }
        }
    }
}

int n, val[maxn], ans[maxn], d[maxn];
vector<int> G[maxn], p[maxn], cnt[maxn];

void dfs(int u, int f)
{
    for(int i=0; i<p[val[u]].size(); i++)
        cnt[u][i]=d[p[val[u]][i]];

    ans[u]=0;
    for(int i=0; i<G[u].size(); i++)
    {
        int v=G[u][i];
        if(v==f)continue ;
        dfs(v, u);
    }
    for(int i=0; i<p[val[u]].size(); i++)
        {
            int x=p[val[u]][i];
            ++d[x];
            ans[u]+=mu[x]*(d[p[val[u]][i]]-cnt[u][i]);
        }
}

int main()
{
    Moblus();
    for(int i=1; i<=1e5; i++)
    {
        p[i].clear();
        for(int j=1; j*j<=i; j++)if(i%j==0)
        {
            p[i].pb(j);
            if(j!=i/j)p[i].pb(i/j);
        }
    }
    int kase=0;
    while(~scanf("%d", &n))
    {
        for(int i=1; i<=n; i++)
            G[i].clear();
        clr(d, 0);
        for(int i=0; i<n-1; i++)
        {
            int u, v;
            scanf("%d%d", &u, &v);
            G[u].pb(v), G[v].pb(u);
        }
        for(int i=1; i<=n; i++)
        {
            scanf("%d", val+i);
            cnt[i].resize(p[val[i]].size(), 0);
        }
        dfs(1, -1);
        printf("Case #%d:", ++kase);
        for(int i=1; i<=n; i++)
            printf(" %d", ans[i]);
        puts("");
    }
    return 0;
}
