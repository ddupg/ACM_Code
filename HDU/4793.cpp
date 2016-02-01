#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <string>
#include <cmath>
using namespace std;

struct Point
{
    double x, y;
    Point(double x=0, double y=0):x(x), y(y){}
};
typedef Point Vector;

Vector operator + (Vector a, Vector b)
{
    return Vector(a.x+b.x, a.y+b.y);
}
Vector operator - (Vector a, Vector b)
{
    return Vector(a.x-b.x, a.y-b.y);
}
Vector operator * (Vector a, double p)
{
    return Vector(a.x*p, a.y*p);
}
Vector operator / (Vector a, double p)
{
    return Vector(a.x/p, a.y/p);
}
bool operator <(const Point &a, const Point &b)
{
    return a.x<b.x || (a.x==b.x && a.y<b.y);
}
const double eps=1e-10;
int dcmp(double x)
{
    if(fabs(x)<eps)return 0;
    else return x<0?-1:1;
}
double dot(Vector a, Vector b)
{
    return a.x*b.x+a.y*b.y;
}
double Length(Vector a)
{
    return sqrt(dot(a, a));
}

double cross(Vector a, Vector b)
{
    return a.x*b.y-a.y*b.x;
}

Point get_line_projection(Point p, Point a, Point b)
{
    Vector v=b-a;
    return a+v*(dot(v, p-a)/dot(v, v));
}

double gougu(double c, double a)
{
    return sqrt(c*c-a*a);
}

double Rm, R, r;
Point s, v;
Vector L;

int main()
{
    while(~scanf("%lf%lf%lf%lf%lf%lf%lf", &Rm, &R, &r, &s.x, &s.y, &v.x, &v.y))
    {
        if(Length(s+v)>Length(s-v))
        {
            printf("0.000\n");
            continue ;
        }

        if(!dcmp(v.y))
        {
            L.x=0;
            L.y=10;
        }
        else
        {
            L.x=10.0;
            L.y=-1.0*v.x*10.0/v.y;
        }

        Point P=get_line_projection(s, Point(0, 0), L); //投影点

        double dis=Length(P);  //投影点到原点距离

        if(dcmp(dis-R-r)>0)
        {
            printf("0.000\n");
            continue ;
        }

        double dis1=gougu(R+r, dis);

        if(dcmp(dis-Rm-r)>0)
        {
            printf("%.3lf\n", 2*dis1/sqrt(v.x*v.x+v.y*v.y));
            continue ;
        }

        double dis2=gougu(Rm+r, dis);

        printf("%.3lf\n", 2*(dis1-dis2)/sqrt(v.x*v.x+v.y*v.y));
    }
    return 0;
}
