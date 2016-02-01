#include <iostream>
#include <cstdio>
#include <cmath>
using namespace std;
const double eps=1e-10;

int main()
{
    int T, kase=0, k1, k2;
    double p;
    scanf("%d", &T);
    while(T--)
    {
        scanf("%lf %d %d", &p, &k1, &k2);
        if (p>1-eps)
        {
            printf("Case %d: %lf\n", ++kase, 1.0*k2);
            continue;
        }
        if (p<eps)
        {
            printf("Case %d: %lf\n",++kase, 1.0*k1);
            continue;
        }
        if(!k1 || !k2)
        {
            printf("Case %d: %lf\n", ++kase, 0);
            continue ;
        }
        double c1=(1-pow(1-p, k1-1))/p, c2=(1-pow(p, k2-1))/(1-p);
        double x=(p*c1*c2+c1)/(1-p*c1*c2*(1-p));
        double y=(1-p)*x*c2+c2;
        printf("Case %d: %lf\n", ++kase, (1-p)*x+p*y+1);
    }
    return 0;
}
