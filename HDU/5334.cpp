#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#define clr(a, x) memset(a, x, sizeof a)
using namespace std;
typedef long long LL;

LL k;
int num, cnt[110000], sum;

void solve(int L, LL K)
{
    if(!K)
    {
        for(int i=1; i<=L; i++)
            cnt[++num]=1, sum++;
        return ;
    }
    LL l=1, r=L<<1;
    while(l<r)
    {
        LL mid=l+r+1>>1;
        if(mid*mid-mid<=K)
            l=mid;
        else r=mid-1;
    }
    while(K>=l*l-l)
    {
        L-=l, K-=l*l-l;
        cnt[++num]=l;
        sum+=l;
    }
    solve(L, K);
}

int main()
{
    while(cin>>k)
    {
        if(k<=1e5)
        {
            printf("%I64d\n", k);
            for(int i=0; i<k; i++)
            {
                if(i)putchar(' ');
                putchar('1');
            }
            putchar('\n');
        }
        else
        {
            clr(cnt, 0);
            sum=num=0;
            LL l;
            for(l=1; l*l+l<2*k; l++);
            solve(l, l*l+l-2*k);
            int first=0;
            printf("%d\n", sum);
            for(int i=1; i<=num; i++)
                for(int j=0; j<cnt[i]; j++)
                {
                    if(first)putchar(' ');
                    first=true;
                    printf("%d", i);
                }
            putchar('\n');
        }
    }
    return 0;
}
