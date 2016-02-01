#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
using namespace std;

const double eps=1e-8;

int main()
{
    double L, n, C, LL;
    while(~scanf("%lf%lf%lf", &L, &n, &C))
    {
        if(L<0)break;
        if(n<eps)
        {
            puts("0.000");
            continue ;
        }
        LL=(1+n*C)*L;
        double l=L*0.5, r=1e30, mid, rad;
        for(int i=0; i<200; i++)
        {
            mid=(l+r)*0.5;
            rad=asin(L/(2*mid));
            if(2*rad*mid<LL)
                r=mid;
            else l=mid;
        }
        printf("%.3f\n", l-l*cos(rad));
    }
    return 0;
}
