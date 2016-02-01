#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
using namespace std;

double r[10], ans, pos[10];
int n, p[10];

double getpos(double x, double y, double r)
{
    return x+sqrt((y+r)*(y+r)-(y-r)*(y-r));
}

void work()
{
    pos[0]=r[p[0]];
    double t=2*r[p[0]];
    for(int i=1; i<n; i++)
    {
        double tmp=r[p[i]];
        for(int j=0; j<i; j++)
            tmp=max(tmp, getpos(pos[j], r[p[j]], r[p[i]]));
        pos[i]=tmp;
        t=max(t, pos[i]+r[p[i]]);
    }
    ans=min(t, ans);
}

int main()
{
    int T;
    scanf("%d", &T);
    while(T--)
    {
        scanf("%d", &n);
        ans=0;
        for(int i=0; i<n; i++)
        {
            scanf("%lf", r+i);
            p[i]=i;
            ans+=2*r[i];
        }
        do{
            work();
        }while(next_permutation(p, p+n));
        printf("%.3lf\n", ans);
    }
    return 0;
}
