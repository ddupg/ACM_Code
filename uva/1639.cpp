#include <cstdio>
#include <algorithm>
#include <iostream>
#include <cmath>
using namespace std;

int main()
{
    double p, p1, p2;
    int n, kase=0;
    while(~scanf("%d%lf", &n, &p))
    {
        long double C=log(1);
        p1=(n+1)*log(p);
        p2=(n+1)*log(1.0-p);
        double ans=0.0;
        for(int i=n, j=1; i>0; i--, j++)
        {
            long double v1=C+p1+(n-i)*log(1.0-p);
            long double v2=C+p2+(n-i)*log(p);
            ans+=i*(exp(v1)+exp(v2));
            C=C+log(n+j)-log(j);
        }
        printf("Case %d: %.6lf\n", ++kase, ans);
    }
    return 0;
}
