#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;
typedef long long LL;

int main()
{
    int T;
    scanf("%d", &T);
    while(T--)
    {
        LL n, ans=0;
        scanf("%lld", &n);
        for(LL i=1, j=n; i*i<=n; i++, j=n/i)
        {
            ans+=i*(n/i-n/(i+1));
            if(i!=j)
                ans+=j*(n/j-n/(j+1));
        }
        printf("%lld\n", ans);
    }
    return 0;
}
