#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
using namespace std;
typedef long long LL;

void exgcd(LL a, LL b, LL &d, LL& x, LL& y)
{
    if(!b)
    {
        d=a, x=1, y=0;
    }
    else
    {
        exgcd(b, a%b, d, y, x);
        y-=x*(a/b);
    }
}

int main()
{
    LL a, b, c, d, x, y, x1, x2, y1, y2;
    cin>>a>>b>>c;
    cin>>x1>>x2>>y1>>y2;
    c=-c;
    if(c<0)
        a=-a, b=-b, c=-c;
    if(a<0)
    {
        a=-a;
        swap(x1, x2);
        x1=-x1, x2=-x2;
    }
    if(b<0)
    {
        b=-b;
        swap(y1, y2);
        y1=-y1, y2=-y2;
    }

    if(a==0 && b==0)
    {
        if(c==0)
            cout<<(x2-x1+1)*(y2-y1+1)<<endl;
        else cout<<0<<endl;
    }
    else if(a==0)
    {
        if(c%b==0 && c/b>=y1 && c/b<=y2)
            cout<<x2-x1+1<<endl;
        else cout<<0<<endl;
    }
    else if(b==0)
    {
        if(c%a==0 && c/a>=x1 && c/a<=x2)
            cout<<y2-y1+1<<endl;
        else cout<<0<<endl;
    }
    else
    {
        d=__gcd(a, b);
        if(c%d)
        {
            cout<<0<<endl;
            return 0;
        }
        a/=d, b/=d, c/=d;
        exgcd(a, b, d, x, y);
        x*=c, y*=c;

        LL r=min(floor(1.0*(x2-x)/b), floor(1.0*(y-y1)/a));
        LL l=max(ceil(1.0*(x1-x)/b), ceil(1.0*(y-y2)/a));
        if(l>r)
            cout<<0<<endl;
        else cout<<r-l+1<<endl;
    }
    return 0;
}
