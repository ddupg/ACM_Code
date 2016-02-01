#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
typedef long long LL;
const int maxn=25;
int n, sum, g[maxn<<1][maxn];
LL d[maxn<<1][maxn][550];

LL dp()
{
    for(int i=1; i<=n; i++)
        d[n*2-1][i][g[2*n-1][i]]=1;
    for(int i=2*n-1; i>n; i--)
        for(int j=1; j<=i+1-n; j++)
            for(int k=0; k<=sum; k++)if(d[i][j][k])
            {
                int t;
                if(~g[i-1][j] && (t=k+g[i-1][j])<=sum)
                    d[i-1][j][t]+=d[i][j][k];
                if(~g[i-1][j-1] && (t=k+g[i-1][j-1])<=sum)
                    d[i-1][j-1][t]+=d[i][j][k];
            }
    for(int i=n; i>1; i--)
        for(int j=1; j<=n+1-i; j++)
            for(int k=0; k<=sum; k++)if(d[i][j][k])
            {
                int t;
                if(~g[i-1][j] && (t=k+g[i-1][j])<=sum)
                    d[i-1][j][t]+=d[i][j][k];
                if(~g[i-1][j+1] && (t=k+g[i-1][j+1])<=sum)
                    d[i-1][j+1][t]+=d[i][j][k];
            }
    LL ans=0;
    for(int i=1; i<=n; i++)
        if(d[1][i][sum])
            ans+=d[1][i][sum];
    return ans;
}

void dfs(int i, int j, int k)
{
    if(i==n*2-1)return ;
    int t=k-g[i][j];
    if(i<n)
    {
        if(~g[i+1][j-1] && d[i+1][j-1][t])
        {
            putchar('L');
            dfs(i+1, j-1, t);
            return ;
        }
        else if(~g[i+1][j] && d[i+1][j][t])
        {
            putchar('R');
            dfs(i+1, j, t);
            return ;
        }
    }
    else
    {
        if(~g[i+1][j] && d[i+1][j][t])
        {
            putchar('L');
            dfs(i+1, j, t);
            return ;
        }
        else if(~g[i+1][j+1] && d[i+1][j+1][t])
        {
            putchar('R');
            dfs(i+1, j+1, t);
            return ;
        }
    }
}

int main()
{
    while(~scanf("%d%d", &n, &sum) && n+sum)
    {
        memset(d, 0, sizeof d);
        memset(g, -1, sizeof g);
        for(int i=1; i<=n; i++)
            for(int j=1; j<=n-i+1; j++)
                scanf("%d", &g[i][j]);
        for(int i=1; i<n; i++)
            for(int j=1; j<=i+1; j++)
                scanf("%d", &g[n+i][j]);
        LL cnt=dp();
        printf("%lld\n", cnt);
        if(cnt)
        {
            for(int i=1; i<=n; i++)if(d[1][i][sum])
            {
                printf("%d ", i-1);
                dfs(1, i, sum);
                break;
            }
        }
        puts("");
    }
    return 0;
}
