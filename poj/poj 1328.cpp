#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;

int n;
double d;

struct Point
{
    double L, R;
    bool op;
    Point(double x, double y)
    {
        double t=sqrt(d*d-y*y);
        L=x-t;
        R=x+t;
        op=1;
    }
    bool operator < (const Point a)const
    {
        return R<a.R || (R==a.R && L>a.L);
    }
};
vector<Point> p;

int main()
{
    int kase=0;
    while(~scanf("%d%lf", &n, &d) && n)
    {
        int flag=1;
        p.clear();
        for(int i=0; i<n; i++)
        {
            double x, y;
            scanf("%lf%lf", &x, &y);
            if(y>d)flag=0;
            p.push_back(Point(x, y));
        }
        printf("Case %d: ", ++kase);
        if(!flag)
        {
            puts("-1");
            continue ;
        }
        sort(p.begin(), p.end());
        int ans=0;
        for(int i=0; i<n; i++)
        {
            if(p[i].op)
            {
                ans++;
                for(int j=i+1; j<n; j++)
                {
                    if(p[j].L<=p[i].R && p[j].R>=p[i].R)
                        p[j].op=0;
                }
            }
        }
        printf("%d\n", ans);
    }
    return 0;
}
