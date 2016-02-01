#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
typedef long long LL;
LL a[11000], d[11000];

inline LL abs(LL x)
{
    return x>0?x:-x;
}

int main()
{
    int n;
    scanf("%d", &n);
    LL ans=0;
    for(int i=0; i<n; i++)
        scanf("%I64d", a+i);
    sort(a, a+n);
    d[0]=0;
    for(int i=1; i<n; i++)
    {
        d[i]=d[i-1]+(a[i]-a[i-1])*i;
        ans+=d[i];
    }
    printf("%I64d\n", ans<<1);
    return 0;
}
