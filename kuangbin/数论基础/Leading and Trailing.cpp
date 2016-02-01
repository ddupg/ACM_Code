#include <iostream>
#include <cstdio>
#include <cmath>
using namespace std;
typedef long long LL;

int qpow(LL n, int b)
{
    LL ans=1;
    while(b)
    {
        if(b&1)
            (ans*=n)%=1000;
        (n*=n)%=1000;
        b>>=1;
    }
    return ans;
}

int main()
{
    int n, k, T, kase=0;
    scanf("%d", &T);
    while(T-- && ~scanf("%d%d", &n, &k))
        printf("%d...%03d\n", (int)pow(10, 2+fmod(k*log10(n), 1)), qpow(n, k));
    return 0;
}
