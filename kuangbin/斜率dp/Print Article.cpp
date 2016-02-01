#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long LL;
const int maxn=500000+100;

LL sum[maxn], d[maxn], m;
int n, q[maxn];

LL sqr(LL x)
{
    return x*x;
}

LL GetUp(int k, int j)
{
    return d[j]-d[k]+sqr(sum[j])-sqr(sum[k]);
}

LL GetDown(int k, int j)
{
    return 2*(sum[j]-sum[k]);
}

LL GetDP(int i, int j)
{
    return d[j]+sqr(sum[i]-sum[j])+m;
}

int main()
{
    while(~scanf("%d%I64d", &n, &m))
    {
        for(int i=1; i<=n; i++)
        {
            scanf("%I64d", sum+i);
            sum[i]+=sum[i-1];
        }
        int head=0, tail=0;
        q[tail++]=0;
        for(int i=1; i<=n; i++)
        {
            while(head<tail-1 && GetDown(q[head], q[head+1])*sum[i]>=GetUp(q[head], q[head+1]))
                head++;
            d[i]=GetDP(i, q[head]);
            while(head<tail-1 && GetDown(q[tail-1], i)*GetUp(q[tail-2], q[tail-1])>=GetUp(q[tail-1], i)*GetDown(q[tail-2], q[tail-1]))
                tail--;
            q[tail++]=i;
        }
        printf("%I64d\n", d[n]);
    }
    return 0;
}
