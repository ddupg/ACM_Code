#include <cstdio>
using namespace std;
typedef long long LL;

int main()
{
    int T, kase=0;
    scanf("%d", &T);
    while(T--)
    {
        LL n, k, MOD, ans=1, sum=0, x;
        scanf("%lld%lld%lld", &n, &k, &MOD);
        for(int i=0; i<n; i++)
        {
            scanf("%lld", &x);
            (sum+=x)%=MOD;
        }
        LL b=k-1;
        while(b)
        {
            if(b&1)
                (ans*=n)%=MOD;
            (n*=n)%=MOD;
            b>>=1;
        }
        printf("Case %d: %lld\n", ++kase, (k*ans*sum)%MOD);
    }
    return 0;
}
