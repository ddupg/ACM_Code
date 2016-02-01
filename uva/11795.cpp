#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
typedef long long LL;
const int maxn=1<<17;

LL d[maxn];
int n, ALL, f[maxn];

int fun()
{
    char s[20];
    scanf("%s", s);
    int ans=0;
    for(int i=0; s[i]; i++)
        if(s[i]=='1')
            ans|=(1<<i);
    return ans;
}

int main()
{
    int T, kase=0;
    scanf("%d", &T);
    while(T--)
    {
        memset(d, 0, sizeof d);
        memset(f, 0, sizeof f);
        scanf("%d", &n);
        ALL=(1<<n)-1;
        f[0]=fun();
        for(int i=0; i<n; i++)
            f[1<<i]=fun();
        d[0]=1;
        for(int x=0; x<=ALL; x++)if(d[x])
        {
            for(int i=0; i<n; i++)
                if((1<<i&f[x]) && !(1<<i&x))
                {
                    int y=1<<i|x;
                    f[y]=(f[x]|f[1<<i]);
                    d[y]+=d[x];
                }
        }
        printf("Case %d: %lld\n", ++kase, d[ALL]);
    }
    return 0;
}
