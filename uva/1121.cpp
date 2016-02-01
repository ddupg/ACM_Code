#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
using namespace std;

int n, s;
int a[100000+100], sum[100000+100];

int search(int start)
{
    if(sum[n]-sum[start]<s)return -1;
    int lo=start+1, hi=n;
    while(lo<hi)
    {
        int mid=(lo+hi)>>1;
        if(sum[mid]-sum[start]<s)
            lo=mid+1;
        else hi=mid;
    }
    return lo;
}

int main()
{
    while(~scanf("%d%d", &n, &s))
    {
        sum[0]=0;
        for(int i=1; i<=n; i++)
        {
            scanf("%d", a+i);
            sum[i]=sum[i-1]+a[i];
        }
        int ans=1e9;
        for(int i=0; i<n; i++)
        {
            int pos=search(i);
            if(pos==-1)continue ;
            ans=min(ans, pos-i);
        }
        printf("%d\n", ans==1e9?0:ans);
    }
    return 0;
}
