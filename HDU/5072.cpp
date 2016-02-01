#include <iostream>
#include <cstdio>
#include <algorithm>
#include <queue>
#include <cstring>
#define clr(a, x) memset(a, x, sizeof a)
using namespace std;
typedef long long LL;
const int maxn=100000+10;

int n, pr[maxn], a[maxn], cnt[maxn], bit[1<<7];

void init()
{
    for(int i=2; i<maxn; i++)
        if(!pr[i])
            for(int j=i; j<maxn; j+=i)
                pr[j]=i;
    for(int i=1; i<(1<<7); i++)
        for(int j=0; j<7; j++)
            bit[i]+=(i>>j&1);
}

LL get(int x)
{
    LL ans=0;
    int p[10], c=0;
    for(int y=x; y>1; )
    {
        p[c++]=pr[y];
        for(int t=pr[y]; y%t==0; y/=t);
    }
    for(int s=1; s<(1<<c); s++)
    {
        int y=1;
        for(int i=0; i<c; i++)
            if(s>>i&1)
                y*=p[i];
        if(bit[s]&1)ans+=cnt[y];
        else ans-=cnt[y];
    }
    return ans;
}

int main()
{
    init();
    int T;
    scanf("%d", &T);
    while(T--)
    {
        clr(cnt, 0);
        scanf("%d", &n);
        for(int i=0; i<n; i++)
        {
            scanf("%d", a+i);
            cnt[a[i]]++;
        }
        for(int i=1; i<maxn; i++)
            for(int j=2*i; j<maxn; j+=i)
                cnt[i]+=cnt[j];
        LL ans=0;
        for(int i=0; i<n; i++)
        {
            LL t=get(a[i]);
            if(a[i]>1)--t;
            ans+=t*(n-1-t);
        }
        ans=1LL*n*(n-1)*(n-2)/6-(ans>>1);
        printf("%I64d\n", ans);
    }
    return 0;
}
