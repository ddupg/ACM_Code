#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long LL;
const int maxn=2020;

LL d[maxn][maxn];
int n, a[maxn];

LL dp(int l, int r)
{
    if(l==r)return d[l][r]=n*a[l];
    if(~d[l][r])return d[l][r];
    int t=n-(r-l);
    return d[l][r]=max(dp(l+1, r)+t*a[l], dp(l, r-1)+t*a[r]);
}

int main()
{
    while(~scanf("%d", &n))
    {
        for(int i=1; i<=n; i++)
            scanf("%d", a+i);
        memset(d, -1, sizeof d);
        printf("%d\n", dp(1, n));
    }
    return 0;
}
