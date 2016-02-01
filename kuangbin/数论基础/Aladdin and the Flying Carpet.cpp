#include <cstdio>
using namespace std;
typedef long long LL;

int pri[1000000+10], cnt=0;
bool t[1000000+10];
LL a, b;

void init()
{
    for(int i=2; i*i<=1e6; i++)
        if(!t[i])for(int j=i*i; j<=1e6; j+=i)
                t[j]=true;
    for(int i=2; i<=1e6; i++)
        if(!t[i])
            pri[cnt++]=i;
}

LL solve()
{
    if(b*b>a)return 0;
    LL tmp=a;
    LL ans=1;
    for(int i=0; i<cnt && tmp/pri[i]>=pri[i]; i++)
    {
        if(tmp%pri[i]==0)
        {
            int c=0;
            while(tmp%pri[i]==0)
                c++, tmp/=pri[i];
            ans*=c+1;
        }
    }
    if(tmp>1)ans<<=1;
    ans>>=1;
    for(LL i=1; i<b && i*i<=a; i++)
        if(a%i==0)
            ans--;
    return ans;
}

int main()
{
    init();
    int kase=0, T;
    scanf("%d", &T);
    while(T--)
    {
        scanf("%lld%lld", &a, &b);
        printf("Case %d: %lld\n", ++kase, solve());
    }
    return 0;
}
