#include <iostream>
#include <cstring>
#include <algorithm>
#include <cstdio>
#define clr(a, x) memset(a, x, sizeof a)
using namespace std;
typedef long long LL;

int a[50];

int main()
{
    int T, D, L, R, kase=0;
    scanf("%d", &T);
    while(T--)
    {
        scanf("%d%d%d", &D, &L, &R);
        clr(a, 0);
        int cnt=0;
        LL ans=D;
        for(int i=0, t=D; t; t>>=1, i++)
            a[i]=(t&1), cnt+=a[i];
        for(int i=0, c=0; i<50; i++)
        {
            if(!a[i])
            {
                if(cnt+1-c<=R)
                {
                    ans|=(1LL<<i);
                    cnt++;
                    for(int j=0; j<i; j++)
                        if(a[j])a[j]=0, ans^=(1LL<<j), cnt--;
                    for(int j=0; j<i && cnt<L; j++)
                        a[j]=1, ans|=(1LL<<j), cnt++;
                    break;
                }
            }
            else c++;
        }
        printf("Case #%d: %I64d\n", ++kase, ans);
    }
    return 0;
}
