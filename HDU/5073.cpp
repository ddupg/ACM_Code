#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cmath>
using namespace std;

const int maxn=50000+10;
double sum[maxn], a[maxn], seq[maxn];
int n, k;

int main()
{
    int T;
    scanf("%d", &T);
    while(T--)
    {
        scanf("%d%d", &n, &k);
        sum[0]=seq[0]=0;
        for(int i=1; i<=n; i++)
            scanf("%lf", &a[i]);
        sort(a+1, a+1+n);
        for(int i=1; i<=n; i++)
        {
            sum[i]=sum[i-1]+a[i];
            seq[i]=seq[i-1]+a[i]*a[i];
        }
        if(k==n)
        {
            printf("0.0000000000\n");
            continue ;
        }
        double ans=seq[n]-seq[k]-(sum[n]-sum[k])*(sum[n]-sum[k])/(n-k);
        int L, R;
        for(int i=1; i<=k+1; i++)
        {
            L=i;
            R=L+n-k-1;
            ans=min(ans, seq[R]-seq[L-1]-(sum[R]-sum[L-1])*(sum[R]-sum[L-1])/(n-k));
        }
        printf("%.10lf\n", ans);
    }
    return 0;
}
