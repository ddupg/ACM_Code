#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;
typedef long long LL;

int len=0, x[1100];
LL a[100000];

void solve(int x)
{
    a[0]++;
    for(int i=0; i<=len+15; i++)
    {
        a[i]=a[i]*x;
        if(i)
        {
            a[i]+=a[i-1]/10;
            a[i-1]%=10;
        }
    }
    while(a[len])
        a[len+1]+=a[len]/10, a[len]%10, len++;
}

int solve2(int x)
{
    int ans=0;
    for(; x; x/=10)
        ans+=x%10;
    return ans;
}

int main()
{
    int T, n;
    scanf("%d", &T);
    while(T--)
    {
        scanf("%d", &n);
        memset(a, 0, sizeof a);
        for(int i=0; i<n; i++)
            scanf("%d", x+i);
        if(n==0)
        {
            printf("0\n");
            continue ;
        }
        while(x[n-1])
        {
            a[len++]=x[n-1]%10;
            x[n-1]/=10;
        }
        for(int i=n-2; i>=0; i--)
            solve(x[i]);
        int ans=0;
        for(int i=0; i<100000; i++)
            ans+=a[i];
        while((ans=solve2(ans))>9)
            ;
        printf("%d\n", ans);
    }
    return 0;
}
