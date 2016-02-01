#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn=1010;

int n, ans, d[maxn][maxn];
char g[maxn][maxn];

int main()
{
    while(~scanf("%d", &n) && n)
    {
        memset(g, 0, sizeof g);
        for(int i=1; i<=n; i++)
            scanf("%s", g[i]+1);
        int ans=1;
        for(int i=1; i<=n; i++)
            for(int j=1; j<=n; j++)
            {
                if(i==1 || j==n)
                {
                    d[i][j]=1;
                    continue ;
                }
                int k;
                for(k=1; k<=d[i-1][j+1]; k++)
                    if(g[i-k][j]!=g[i][j+k])
                        break;
                if(k>d[i-1][j+1])
                    d[i][j]=d[i-1][j+1]+1;
                else d[i][j]=k;
                ans=max(ans, d[i][j]);
            }
        printf("%d\n", ans);
    }
    return 0;
}
