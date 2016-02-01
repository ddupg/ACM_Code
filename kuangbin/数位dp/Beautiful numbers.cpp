#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;
typedef long long LL;
const int LCM=2520;

int num[20], c[2550], gcd[2550][10];
LL d[20][50][2550];

void init()
{
    int cnt=0;
    for(int i=1; i<=LCM; i++)
        if(LCM%i==0)
        {
            c[i]=cnt++;
            for(int j=1; j<=9; j++)
                gcd[i][j]=__gcd(i, j);
        }
}

LL dfs(int i, int preLcm, int preSum, bool e)
{
    if(i==-1)return preSum%preLcm==0;
    if(!e && ~d[i][c[preLcm]][preSum])return d[i][c[preLcm]][preSum];
    int u=e?num[i]:9;
    LL ans=0;
    for(int j=0; j<=u; j++)
        ans+=dfs(i-1, j?preLcm/gcd[preLcm][j]*j:preLcm, (preSum*10+j)%LCM, e&&j==u);
    return e?ans:d[i][c[preLcm]][preSum]=ans;
}

LL solve(LL x)
{
    int t=0;
    for(; x; x/=10)
        num[t++]=x%10;
    return dfs(t-1, 1, 0, 1);
}

int main()
{
    init();
    int T;
    memset(d, -1, sizeof d);
    scanf("%d", &T);
    while(T--)
    {
        LL a, b;
        scanf("%I64d%I64d", &a, &b);
        printf("%I64d\n", solve(b)-solve(a-1));
    }
    return 0;
}
