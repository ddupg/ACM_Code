#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <vector>
using namespace std;
const int maxn=500000+10;

int n, ar[maxn], a[maxn], b[maxn], cnt;

int lowbit(int x){return x&-x; }
void add(int i, int v)
{
    for(; i<=n; ar[i]+=v, i+=lowbit(i));
}
long long sum(int i)
{
    long long ans=0;
    for(; i>0; ans+=ar[i], i-=lowbit(i));
    return ans;
}

int main()
{
    while(~scanf("%d", &n) && n)
    {
        memset(ar, 0, sizeof ar);
        for(int i=0; i<n; i++)
        {
            scanf("%d", a+i);
            b[i]=a[i];
        }
        sort(a, a+n);
        cnt=unique(a, a+n)-a;
        long long ans=0;
        for(int i=n-1; i>=0; i--)
        {
            b[i]=lower_bound(a, a+cnt, b[i])-a+1;
            ans+=sum(b[i]-1);
            add(b[i], 1);
        }
        cout<<ans<<endl;
    }
    return 0;
}
