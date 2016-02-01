#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <string>
#include <cmath>
#define clr(a, x) memset(a, x, sizeof a)
using namespace std;
const int maxn=330;

struct Circle
{
    double x, y, r;
} c[maxn], o;


struct Edge
{
    int v, nxt;
    double w;
} edge[maxn*maxn];

int n, tot, head[maxn];
int cnt[maxn];

double Len(Circle c)
{
    return sqrt(c.x*c.x+c.y+c.y);
}

void init()
{
    tot=0;
    clr(head, -1);
    clr(cnt, 0);
}

void AddEdge(int u, int v, double w)
{
    edge[tot].v=v;
    edge[tot].nxt=head[u];
    edge[tot].w=w;
    head[u]=tot++;
}

bool spfa()
{

}

int main()
{
    cout<<"afkljasldf";
    /*
    int T;
    scanf("%d", &T);
    while(T--)
    {
        scanf("%d", &n);
        for(int i=0; i<n; i++)
            scanf("%lf%lf%lf", &c[i].x, &c[i].y, &c[i].r);
        scanf("%lf%lf%lf", &o.x, &o.y, &o.r);
        for(int i=0; i<n; i++)
        {
            c[i].x-=o.x;
            c[i].y-=o.y;
            c[i].r+=o.r;
        }
        for(int i=0; i<n; i++)
            for(int j=i+1; j<n; j++)
                if(c[i].r+c[j].r>=sqrt((c[i].x-c[j].x)*(c[i].x-c[j].x)+(c[i].y-c[j].y)*(c[i].y-c[j].y)))
                {
                    double r=acos((c[i].x*c[j].x+c[i].y*c[j].y)/Len(c[i])/Len(c[j]));
                }
    }
    */
    return 0;
}
