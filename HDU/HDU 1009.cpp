#include <iostream>
#include <cstdio>
#include <algorithm>
#include <iomanip>
using namespace std;

struct Node
{
    double J, F;
    bool operator < (const Node a)const
    {
        return J/F>a.J/a.F;
    }
}node[1110];

int main()
{
    int n;
    double m;
    while(scanf("%lf%d", &m, &n) && ~n)
    {
        for(int i=0; i<n; i++)
            scanf("%lf%lf", &node[i].J, &node[i].F);
        sort(node, node+n);
        double ans=0;
        for(int i=0; i<n; i++)
        {
            if(m>=node[i].F)
                ans+=node[i].J, m-=node[i].F;
            else
                ans+=m/node[i].F*node[i].J, m=0;
            if(m<1e-6)break;
        }
        printf("%.3lf\n", ans);
    }
    return 0;
}
