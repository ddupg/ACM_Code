#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cmath>
#define sqr(x) ((x)*(x))
using namespace std;

const double eps=1e-7;

int dcmp(double x)
{
    if(fabs(x)<eps)return 0;
    return x<0?-1:1;
}
struct Point
{
    double x, y;
    Point() {}
    Point(double x, double y):x(x), y(y) {}
    void get()
    {
        scanf("%lf%lf", &x, &y);
    }
    Point operator - (const Point a)const
    {
        return Point(x-a.x, y-a.y);
    }
};
double Cross(Point a, Point b)
{
    return a.x*b.y-a.y*b.x;
}

double Area(Point a, Point b, Point c)
{
    return 0.5*fabs(Cross(a-c, b-c));
}

double Dot(Point a, Point b)
{
    return a.x*b.x+a.y*b.y;
}

bool bet(Point a, Point b, Point c)/**aÔÚbcÖÐ¼ä£¿**/
{
    return dcmp(Cross(b-a, c-a))==0 && dcmp(Dot(b-a, c-a))<0;
}

int main()
{
    int n;
    while(~scanf("%d", &n) && n)
    {
        Point p[20];
        char name[20];
        for(int i=0; i<n; i++)
            scanf("%*c%c %lf %lf", name+i, &p[i].x, &p[i].y);
        double area=0;
        char ans[]="***";
        for(int i=0; i<n; i++)
            for(int j=i+1; j<n; j++)
                for(int k=j+1; k<n; k++)
                {
                    if(!dcmp(Cross(p[i]-p[k], p[j]-p[k])))continue ;
                    bool ok=true;
                    for(int l=0; l<n; l++)if(l!=i && l!=j && l!=k)
                        {
                            double a=Cross(p[i]-p[l], p[j]-p[l]);
                            double b=Cross(p[j]-p[l], p[k]-p[l]);
                            double c=Cross(p[k]-p[l], p[i]-p[l]);
                            if((dcmp(a)>0 && dcmp(b)>0 && dcmp(c)>0) ||
                                    (dcmp(a)<0 && dcmp(b)<0 && dcmp(c)<0)||
                                    bet(p[l], p[i], p[j]) ||
                                    bet(p[l], p[j], p[k]) ||
                                    bet(p[l], p[k], p[i]))
                            {
                                ok=false;
                                break;
                            }
                        }
                    if(ok)
                    {
                        double tmp=Area(p[i], p[j], p[k]);
                        if(tmp>area)
                            area=tmp, ans[0]=name[i], ans[1]=name[j], ans[2]=name[k];
                    }
                }
        cout<<ans<<endl;
    }
    return 0;
}
