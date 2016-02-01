#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <algorithm>
#include <string>
#include <vector>
#include <cmath>
using namespace std;
typedef long long LL;
typedef unsigned long long LLU;
const int maxn=100000+100;

int n, m;
LL s[maxn], p[maxn];
LL d[maxn];

void dp()
{
    d[n-1]=s[n-1]*p[n-1];
    for(int i=n-2; i>=0; i--)
        d[i]=min(s[i]*p[i], d[i+1]);
}

int main()
{
    int t;
    scanf("%d", &t);
    while(t--)
    {
        scanf("%d%d", &n, &m);
        for(int i=0; i<n; i++)
            scanf("%I64d%I64d", &s[i], &p[i]);
        dp();

        while(m--)
        {
            LL x;
            scanf("%I64d", &x);
            int pos=upper_bound(s, s+n, x)-s;
            if(n==pos)
                printf("%I64d\n", x*p[n-1]);
            else
                printf("%I64d\n", min(x*p[pos-1], d[pos]));
        }
    }
    return 0;
}
