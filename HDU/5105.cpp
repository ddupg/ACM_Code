#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cstring>
#include <cmath>
using namespace std;
typedef long long LL;
const double EPS=1e-10;
double a, b, c, d, l, r;
double A, B, C;
double fun(double x)
{
    return fabs(a*x*x*x+b*x*x+c*x+d);
}
//int main()
//{
//    while(~scanf("%lf%lf%lf%lf%lf%lf", &a, &b, &c, &d, &l, &r))
//    {
//        double ans=0;
//        for(int i=0; i<=300000; i++)
//            ans=max(ans, fun(l+(r-l)*i/300000.0));
//        printf("%.2lf\n", ans);
//    }
//    return 0;
//}
int main()
{
    while(~scanf("%lf%lf%lf%lf%lf%lf", &a, &b, &c, &d, &l, &r))
    {
        double ans=max(fun(l), fun(r));
        double A=3.0*a, B=2.0*b, C=c;
        if(fabs(A)<EPS)
        {
            if(fabs(B)>EPS)
            {
                double x=-C/B;
                if(l<x && x<r)
                    ans=max(ans, fun(x));
            }
        }
        else
        {
            double delt=B*B-4.0*A*C;
            if(fabs(delt)>EPS)
            {
                double x1=(-B+sqrt(delt))/(2.0*A), x2=(-B-sqrt(delt))/(2.0*A);
                if(l<=x1 && x1<=r)
                    ans=max(ans, fun(x1));
                if(l<=x2 && x2<=r)
                    ans=max(ans, fun(x2));
            }
        }
        printf("%.2lf\n", ans);
    }
    return 0;
}

