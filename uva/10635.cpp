#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cstring>
#include <vector>
#include <set>
using namespace std;
typedef long long LL;
const int maxn = 250*250+100;
const int oo = 0x3f3f3f3f;

int num[maxn], s[maxn], g[maxn], d[maxn];

int main()
{
    int T, kase=0, t, p, q, x;
    scanf("%d", &T);
    while(T--)
    {
        memset(num, 0, sizeof num);
        scanf("%d%d%d", &t, &p, &q);
        for(int i=1; i<=p+1; i++)
        {
            scanf("%d", &x);
            num[x]=i;
        }
        int n=0;
        for(int i=1; i<=q+1; i++)
        {
            scanf("%d", &x);
            if(num[x])s[n++]=num[x];
        }
        int ans=0;
        for(int i=1; i<=n; i++)g[i]=oo;
        for(int i=0; i<n; i++)
        {
            int k=lower_bound(g+1, g+1+n, s[i])-g;
            d[i]=k;
            g[k]=s[i];
            ans=max(d[i], ans);
        }
        printf("Case %d: %d\n", ++kase, ans);
    }
    return 0;
}
