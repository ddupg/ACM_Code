#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <vector>
using namespace std;
const int maxn=220;
const double oo=1e10;

struct Point
{
    double x, y;
    Point(double x, double y):x(x), y(y){}
};

int tot;
double d[maxn][maxn];
vector<Point> p;

void init()
{
    for(int i=0; i<maxn; i++)
        for(int j=0; j<maxn; j++)
            d[i][j]=i==j?0:oo;
    p.clear();
}

double dist(Point a, Point b)
{
    return sqrt((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y));
}

void read()
{
    double x, y;
    for(int i=0; i<2; i++)
    {
        scanf("%lf%lf", &x, &y);
        p.push_back(Point(x, y));
    }
    d[0][1]=d[1][0]=dist(p[0], p[1])*3.0/500;
    tot=2;
    int flag=0;
    while(~scanf("%lf%lf", &x, &y))
    {
        if(x==-1 && y==-1)flag=0;
        else
        {
            p.push_back(Point(x, y));
            for(int i=0; i<tot-flag; i++)
                d[i][tot]=d[tot][i]=dist(p[i], p[tot])*3.0/500;
            if(flag)
                d[tot][tot-1]=d[tot-1][tot]=dist(p[tot], p[tot-1])*3.0/2000;
            flag=1;
            tot++;
        }
    }
}

double floyd()
{
    for(int k=0; k<tot; k++)
        for(int i=0; i<tot; i++)
            for(int j=0; j<tot; j++)
                d[i][j]=min(d[i][j], d[i][k]+d[k][j]);
    return d[0][1];
}

int main()
{
    init();
    read();
    printf("%.0lf\n", floyd());
    return 0;
}
