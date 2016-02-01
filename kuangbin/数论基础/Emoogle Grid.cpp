#include <iostream>
#include <cstdio>
#include <set>
#include <cmath>
#include <map>
using namespace std;
typedef long long LL;
const LL mod=1e8+7;

set<pair<LL, LL> > nd;
LL power(LL n, LL b)
{
    LL ans=1;
    while(b)
    {
        if(b&1)
            ans*=n, ans%=mod;
        n*=n, n%=mod;
        b>>=1;
    }
    return ans;
}

void exgcd(LL a, LL b, LL &d, LL &x, LL &y)
{
    if( b == 0 ) { d = a; x = 1; y = 0; }
    else { exgcd(b, a%b, d, y, x); y -= x*(a/b); }
}

LL inv(LL a, LL mod)
{
    LL d, x, y;
    exgcd(a, mod, d, x, y);
    return d == 1 ? (x+mod)%mod : -1;
}

LL log_mod(LL a,LL b,LL n)
{
    LL m,v,e=1,i;
    m=(LL)sqrt(n+0.5);
    v=inv(power(a,m),n);
    map<LL,LL>x;
    x[1]=0;
    for(i=1;i<m;i++)
    {
        e=(e*a)%n;
        if(!x.count(e))x[e]=i;
    }
    for(i=0;i<m;i++)
    {
        if(x.count(b))return i*m+x[b];
        b=(b*v)%n;
    }
    return -1;
}

int main()
{
    int T, kase=0;
    LL n, k, b, r;
    scanf("%d", &T);
    while(T--)
    {
        scanf("%lld%lld%lld%lld", &n, &k, &b, &r);
        nd.clear();
        LL maxx=1;
        for(int i=0; i<b; i++)
        {
            LL x, y;
            scanf("%lld%lld", &x, &y);
            nd.insert(make_pair(x, y));
            maxx=max(maxx, x);
        }
        LL cnt=n;
        for(set<pair<LL, LL> >::iterator i=nd.begin(); i!=nd.end(); i++)
        {
            if(i->first==1)
                cnt--;
            if(i->first<maxx && !nd.count(make_pair(i->first+1, i->second)))
                cnt++;
        }
        LL c=power(k, cnt)*power(k-1, (maxx*n-b-cnt))%mod;
        if(c==r)
        {
            printf("Case %d: %lld\n", ++kase, maxx);
            continue ;
        }
        cnt=n;
        for(set<pair<LL, LL> >::iterator i=nd.begin(); i!=nd.end(); i++)
        {
            if(i->first==1)
                cnt--;
            if(!nd.count(make_pair(i->first+1, i->second)))
                cnt++;
        }
        c=power(k, cnt)*power(k-1, ((maxx+1)*n-b-cnt))%mod;
        if(c==r)
        {
            printf("Case %d: %lld\n", ++kase, maxx+1);
            continue ;
        }

        printf("Case %d: %lld\n", ++kase, maxx+1+log_mod(power(k-1, n), r*inv(c, mod)%mod, mod));
    }
    return 0;
}
