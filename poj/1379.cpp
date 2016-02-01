#include <iostream>
#include <cstring>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <ctime>
#define sqr(x) ((x)*(x))
using namespace std;

const double oo=1e15;
const double eps=1e-3;
const double delet=0.85;
const double PI=acos(-1.0);

struct Point
{
    double x, y;
} p[1100], ans[30];

int n;
double X, Y, best[30];

double dist(Point a, Point b)
{
    return sqrt(sqr(a.x-b.x)+sqr(a.y-b.y));
}

double get(Point a)
{
    double ans=oo;
    for(int i=0; i<n; i++)
        ans=min(ans, dist(a, p[i]));
    return ans;
}

bool inside(Point a)
{
    return a.x>eps && a.y>eps && a.x<X+eps && a.y<Y+eps;
}

int main()
{
    int T;
    scanf("%d", &T);
    srand(time(NULL));
    while(T--)
    {
        scanf("%lf%lf%d", &X, &Y, &n);
        for(int i=0; i<n; i++)
            scanf("%lf%lf", &p[i].x, &p[i].y);
        for(int i=0; i<15; i++)
        {
            ans[i].x=(rand()%1000+1)/1000.0*X;
            ans[i].y=(rand()%1000+1)/1000.0*Y;
            best[i]=get(ans[i]);
        }

        for(double step=max(X, Y)/sqrt(1.0*n); step>eps; step*=delet)
        {
            for(int i=0; i<15; i++)
            {
                Point pre=ans[i], cur;
                for(int j=0; j<35; j++)
                {
                    double angle=(rand()%1000+1)/1000.0*PI*2;
                    cur.x=pre.x+cos(angle)*step;
                    cur.y=pre.y+sin(angle)*step;
                    if(!inside(cur))continue ;
                    double tmp=get(cur);
                    if(tmp>best[i])
                    {
                        ans[i]=cur;
                        best[i]=tmp;
                    }
                }
            }
        }
        int k=0;
        for(int i=1; i<15; i++)
            if(get(ans[i])>get(ans[k]))
                k=i;
        printf("The safest point is (%.1f, %.1f).\n", ans[k].x, ans[k].y);
    }
    return 0;
}
