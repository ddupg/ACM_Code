#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;
const int maxn=100000+100;

inline int read()
{
    char ch = getchar();
    while (ch < '0' || ch > '9') ch = getchar();
    int num = 0;
    while (ch >= '0' && ch <= '9')
    {
        num = num * 10 + ch - '0';
        ch = getchar();
    }
    return num;
}

int n, k;
int sum[maxn];

double getVal(int i, int j)
{
    return (sum[i]-sum[j])*1.0/(i-j);
}

int main()
{
    while(~scanf("%d%d", &n, &k))
    {
        sum[0]=0;
        double ans=0;
        for(int i=1 ; i<=n; i++)
        {
            sum[i]=read();
            sum[i]+=sum[i-1];
        }
        int q[maxn], head=0, tail=0;
        for(int i=k; i<=n; i++)
        {
            while(head<tail-1 && getVal(i-k, q[tail-1])<=getVal(q[tail-1], q[tail-2]))
                --tail;
            q[tail++]=i-k;
            while(head<tail-1 && getVal(i, q[head])<getVal(i, q[head+1]))
                ++head;
            ans=max(ans, getVal(i, q[head]));
        }
        printf("%.2lf\n", ans);
    }
    return 0;
}
