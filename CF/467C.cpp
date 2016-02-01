#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long LL;
const int maxn=5020;

LL sum[maxn], d[maxn][maxn];
int n, m, k;

int main()
{
    scanf("%d%d%d", &n, &m, &k);
    for(int i=1; i<=n; i++)
    {
        scanf("%I64d", sum+i);
        sum[i]+=sum[i-1];
    }
    for(int j=1; j<=k; j++)
    {
        LL tmp=0;
        for(int i=m; i<=n; i++)
        {
            tmp=max(tmp, d[i-m][j-1]);
            d[i][j]=tmp+sum[i]-sum[i-m];
        }
    }
    LL ans=0;
    for(int i=m; i<=n; i++)
        ans=max(ans, d[i][k]);
    printf("%I64d\n", ans);
    return 0;
}
