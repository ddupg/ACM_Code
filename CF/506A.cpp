#include <iostream>
#include <cstdio>
#include <algorithm>
#include <map>
using namespace std;
const int maxn=30010;

int vis[maxn];
int dp[maxn][500], base=250; //base=250

int main()
{
    int n, d, x, ans=1, limit;
    scanf("%d%d", &n, &d);
    while(n--)
    {
        scanf("%d", &x);
        vis[limit=x]++;
    }

    dp[d][base]=vis[d]+1;
    for(int i=d; i<=limit; i++)
    {
        for(int j=0; j<=500; j++)
        {
            if(!dp[i][j])continue ;
            ans=max(ans, dp[i][j]);
            int jump=j-base+d;
            for(int k=max(1, jump-1); k<=jump+1; k++)
            {
                if(i+k<=limit)
                {
                    dp[i+k][k-d+base]=max(dp[i+k][k-d+base], dp[i][j]+vis[i+k]);
                }
            }
        }
    }
    printf("%d\n", ans-1);
    return 0;
}
