#include <cstdio>
using namespace std;
typedef long long LL;

int main()
{
    int T, kase=0;
    LL n;
    scanf("%d", &T);
    while(T--)
    {
        scanf("%lld", &n);
        LL ans=0;
        for(LL i=1; i*i<=n; i++)
        {
            ans++;
            if(2*i*i<=n)
                ans++;
        }
        printf("Case %d: %lld\n", ++kase, n-ans);
    }
    return 0;
}
