#include <cstdio>
using namespace std;
typedef long long LL;
const int maxn=11000000;

bool vis[maxn+10];
int pri[maxn/10+10], c=0;

void init()
{
    for(int i=2; i*i<=maxn; i++)
        if(!vis[i])for(int j=i*i; j<=maxn; j+=i)
                vis[j]=true;
    for(int i=2; i<=maxn; i++)
        if(!vis[i])pri[c++]=i;
}

int main()
{
    init();
    int T, kase=0;
    scanf("%d", &T);
    while(T--)
    {
        LL n, tmp, ans=1;
        scanf("%lld", &n);
        tmp=n;
        for(int i=0; tmp/pri[i]>=pri[i] && i<c; i++)
            if(tmp%pri[i]==0)
            {
                int cnt=0;
                while(tmp%pri[i]==0)
                    cnt++, tmp/=pri[i];
                ans*=(cnt<<1)+1;
            }
        if(tmp>1)
            ans+=(ans<<1);
        printf("Case %d: %lld\n", ++kase, ans+1>>1);
    }
    return 0;
}
