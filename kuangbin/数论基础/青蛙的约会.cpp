#include <iostream>
#include <cstdio>
using namespace std;
typedef long long LL;

void exgcd(LL a, LL b, LL& d, LL& x, LL& y)
{
    if(!b){d=a; x=1; y=0; }
    else{exgcd(b, a%b, d, y, x); y-=x*(a/b); }
}

int main()
{
    LL s, t, n, m, L;
    while(cin>>s>>t>>m>>n>>L)
    {
        LL a=n-m, b=L, c=s-t, d, x, y;
        exgcd(a, b, d, x, y);
        if(c%d)
        {
            puts("Impossible");
            continue ;
        }
        b/=d;
        x*=c/d;
        x=x-x/b*b;
        if(x<0)x+=b;
        cout<<x<<endl;
    }
    return 0;
}
