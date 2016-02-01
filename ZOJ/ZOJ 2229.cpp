#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cmath>
using namespace std;

int main()
{
    int n;
    double v, t;
    while(~scanf("%d", &n) && n)
    {
        double ans=1e9;
        while(n--)
        {
            scanf("%lf%lf", &v, &t);
            if(v<=0 || t<0)continue ;
            ans=min(ans, 4.5*3600/v+t);
        }
        printf("%.0lf\n", ceil(ans));
    }
    return 0;
}
