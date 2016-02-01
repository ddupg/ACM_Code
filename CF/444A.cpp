#include <iostream>
#include <cstdio>
using namespace std;

int val[550], n, m;

int main()
{
    scanf("%d%d", &n,&m);
    for(int i=1; i<=n; i++)
        scanf("%d", val+i);
    double ans=0;
    while(m--)
    {
        int u, v, c;
        scanf("%d%d%d", &u, &v, &c);
        ans=max(ans, 1.0*(val[u]+val[v])/c);
    }
    printf("%.15lf\n", ans);
}
