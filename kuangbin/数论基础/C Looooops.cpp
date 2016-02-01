#include <iostream>
#include <cstdio>
using namespace std;
typedef long long LL;

void exgcd(LL a, LL b, LL& d, LL& x, LL& y)
{
    if(!b){d=a, x=1, y=0; }
    else {exgcd(b, a%b, d, y, x); y-=x*(a/b); }
}

int main()
{
    LL A, B, C, D, k;
    while(cin>>A>>B>>C>>k && A+B+C+k)
    {
        D=(1LL<<k);
        LL a=C, b=D, c=B-A, x, y, d;
        exgcd(a, b, d, x, y);
        if(c%d)
        {
            puts("FOREVER");
            continue ;
        }
        x=(x*(c/d))%b;
        x=(x%(b/d)+b/d)%(b/d);
        cout<<x<<endl;
    }
    return 0;
}
