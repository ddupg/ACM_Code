#include <iostream>
#include <cstring>
#include <algorithm>
#include <cstdio>
#include <cmath>
using namespace std;
const int maxn=50010;
typedef long long LL;

int n;
LL x[maxn], p[maxn], s[maxn], ps[maxn];

LL func(int k)
{
//    int k=floor(pos);
//    double ans=0;
//    k=upper_bound(x+1, x+n+1, k)-x-1;
    LL a=x[k]*s[k]-ps[k];
    LL b=ps[n]-ps[k]-(s[n]-s[k])*x[k];
//    cout<<pos<<": "<<a<<" "<<b<<endl;
    return a+b;
}

int main()
{
//    long double L=1e9, R=0;
    scanf("%d", &n);
    for(int i=1; i<=n; i++)
    {
//        scanf("%lf%lf", x+i, p+i);
        cin>>x[i]>>p[i];
        s[i]=s[i-1]+p[i];
        ps[i]+=ps[i-1]+p[i]*x[i];
//        L=min(L, x[i]);
//        R=max(R, x[i]);
    }
    LL ans=1, Min=func(1);
    for(int i=2; i<=n; i++)
    {
        double tmp=func(x[i]);
        if(tmp<Min)
        {
            Min=tmp;
            ans=i;
        }
    }
    cout<<x[ans]<<".00000"<<endl;
//    while(fabs(R-L)>1e-8)
//    {
//        double d=(R-L)/3.0;
//        if(func(L+d)>func(R-d))
//            L+=d;
//        else R-=d;
//    }
//    printf("%.5lf\n", L);
    return 0;
}
