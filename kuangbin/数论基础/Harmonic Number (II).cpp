#include <cstdio>
using namespace std;
typedef long long LL;

int main()
{
    int T, kase=0;
    scanf("%d", &T);
    while(T--)
    {
        LL n, ans=0;
        scanf("%lld", &n);
        for(LL i=1; i*i<=n; i++)
        {
            ans+=n/i;
            LL tmp=n/i-n/(i+1);
            if(n/i!=i)
                ans+=tmp*i;
        }
        printf("Case %d: %lld\n", ++kase, ans);
    }
    return 0;
}
