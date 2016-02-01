#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <algorithm>
using namespace std;
const int maxn=10000+10;
const double PI=acos(-1.0);

double r[maxn];
int n, f;

bool ok(double x)
{
    int cnt=0;
    for(int i=0; i<n; i++)
    {
        cnt+=floor(r[i]/x);
        if(cnt>=f)return true;
    }
    return false;
}

int main()
{
    int T, kase;
    scanf("%d", &T);
    while(T--)
    {
        scanf("%d%d", &n, &f);
        ++f;
        double L=0, R=0;
        for(int i=0; i<n; i++)
        {
            scanf("%lf", r+i);
            r[i]=PI*r[i]*r[i];
            R=max(R, r[i]);
        }
        while(R-L>1e-5)
        {
            double mid=(R+L)/2;
            if(ok(mid))
                L=mid;
            else R=mid;
        }
        printf("%.4lf\n", L);
    }
    return 0;
}
