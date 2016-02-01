#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
typedef long long LL;
const int maxn=1000000+100;

LL q[maxn], sum[maxn], d[maxn];
int head, tail, n, m;

LL getUp(int j, int k)
{
    return (d[j]+sum[j+1]*sum[j+1])-(d[k]+sum[k+1]*sum[k+1]);
}

LL getDown(int j, int k)
{
    return 2*(sum[j+1]-sum[k+1]);
}

LL getDP(int i, int j)
{
    return d[j]+m+(sum[i]-sum[j+1])*(sum[i]-sum[j+1]);
}

int main()
{
    while(~scanf("%d%d", &n, &m) && n+m)
    {
        for(int i=1; i<=n; i++)
            scanf("%I64d", sum+i);
        sort(sum+1, sum+1+n);
        head=tail=0;
        q[tail++]=0;
        for(int i=1; i<=n; i++)
        {
            while(head+1<tail && getUp(q[head+1], q[head])<=sum[i]*getDown(q[head+1], q[head]))
                head++;
            d[i]=getDP(i, q[head]);
            while(head+1<tail && getUp(i, q[tail-1])*getDown(q[tail-1], q[tail-2])<=getUp(q[tail-1], q[tail-2])*getDown(i, q[tail-1]))
                tail--;
            q[tail++]=i;
        }
        printf("%I64d\n", d[n]);
    }
    return 0;
}
