#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;
typedef long long LL;
const int maxn=110;
const LL mod=1000000007;

LL C[maxn*maxn][maxn], d[maxn][maxn*maxn];
int a[maxn], n;

void init()
{
    C[0][0]=1;
    for(int i=1; i<=10010; i++)
    {
        C[i][0]=C[i][i]=1;
        for(int j=1; j<min(i, 105); j++)
            C[i][j]=(C[i-1][j]+C[i-1][j-1])%mod;
    }
}

int main()
{
    init();
    int kase=0;
    while(~scanf("%d", &n))
    {
        for(int i=1; i<=n; i++)
            scanf("%d", a+i);
        memset(d, 0, sizeof d);
        for(int i=0; i<=a[1]; i++)
            d[1][i]=1;
        int sum=a[1];
        for(int i=2; i<=n; i++)
        {
            sum+=a[i];
            for(int j=0; j<=sum; j++)
                for(int k=0; k<=min(a[i], j); k++)
                    d[i][j]=(d[i][j]+d[i-1][j-k]*C[j][k])%mod;
        }
        LL ans=0;
        for(int i=1; i<=sum; i++)
            ans=(ans+d[n][i])%mod;
        printf("Case %d: %I64d\n", ++kase, ans);
    }
    return 0;
}
