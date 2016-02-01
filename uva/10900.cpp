#include <iostream>
#include <cstdio>
using namespace std;

int main()
{
    int n;
    double t, d[35];
    while(~scanf("%d%lf", &n, &t) && n)
    {
        d[n]=1<<n;
        for(int i=n-1; i>=0; i--)
        {
            double p0=max(t, (1<<i)/d[i+1]);
            double p1=(p0-t)/(1-t);
            d[i]=(1<<i)*p1+(1+p0)/2.0*d[i+1]*(1-p1);
        }
        printf("%.3lf\n", d[0]);
    }
    return 0;
}
