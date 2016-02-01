#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long LL;
const int maxn=50050;
int n, x[maxn];
LL a[maxn], b[maxn], bit[maxn];
int lowbit(int x)
{
    return x&(-x);
}
int query(int x)
{
    int ans=0;
    while(x>0)
    {
        ans+=bit[x];
        x-=lowbit(x);
    }
    return ans;
}
void update(int x)
{
    while(x<=n)
    {
        bit[x]++;
        x+=lowbit(x);
    }
}

int main()
{
    int T;
    scanf("%d", &T);
    while(T--)
    {
        memset(bit, 0, sizeof(bit));
        scanf("%d", &n);
        for(int i=1; i<=n; i++)
        {
            scanf("%d", x+i);
            a[i]=query(x[i]);
            update(x[i]);
        }
        memset(bit, 0, sizeof(bit));
        for(int i=n; i>=1; i--)
        {
            b[i]=n-i-query(x[i]);
            update(x[i]);
        }
        LL sum=0, ans=0;
        for(int i=1; i<n; i++)
        {
            ans+=sum*b[i];
            sum+=a[i];
        }
        printf("%I64d\n", ans);
    }
    return 0;
}
