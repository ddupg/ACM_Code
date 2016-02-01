#include <cstdio>
#include <cstring>
#include <iostream>
typedef long long LL;
using namespace std;
const int maxn=100000;

bool vis[maxn+10], v[maxn+10];
LL pri[maxn+10];
int cnt=0;

void init()
{
    for(int i=2; i*i<=maxn; i++)
        if(!vis[i])for(int j=i*i; j<=maxn; j+=i)
            vis[j]=true;
    for(int i=2; i<=maxn; i++)
        if(!vis[i])pri[cnt++]=i;
}

int main()
{
    init();
    int T, kase=0;
    scanf("%d", &T);
    while(T--)
    {
        LL a, b;
        int ans=0;
        scanf("%lld%lld", &a, &b);
        memset(v, 0, sizeof v);
        for(int i=0; b/pri[i]>=pri[i]; i++)
            for(LL j=pri[i]*max(2LL, a/pri[i]); j<=b; j+=pri[i])
                if(j>=a)
                    v[j-a]=true;

        for(int i=max(a, 2LL); i<=b; i++)
            if(!v[i-a])
                ans++;
        printf("Case %d: %d\n", ++kase, ans);
    }
    return 0;
}
