#include <cstdio>
#include <algorithm>
#include <cmath>
using namespace std;
const int maxn=11000;

double p[1000000+10];

int main()
{
    for(int i=1; i<=1e6; i++)
        p[i]=p[i-1]+1.0/i;
    int T, kase=0;
    scanf("%d", &T);
    while(T--)
    {
        int n;
        double ans;
        scanf("%d", &n);
        if(n<=1e6)
            ans=p[n];
        else ans=0.57721566490153286060651209+log(n)+1.0/(2*n);
        printf("Case %d: %.10lf\n", ++kase, ans);
    }
    return 0;
}
