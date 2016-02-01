#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
using namespace std;
const int maxn=1100;
int n, f[maxn];
double d, x[maxn], y[maxn];
bool ok[maxn];

int find(int x)
{
    return x==f[x]?x:f[x]=find(f[x]);
}

double dis(int i, int j)
{
    return sqrt((x[i]-x[j])*(x[i]-x[j])+(y[i]-y[j])*(y[i]-y[j]));
}

int main()
{
    scanf("%d%lf", &n, &d);
    memset(ok, 0, sizeof(ok));
    for(int i=1; i<=n; i++)
        f[i]=i;
    for(int i=1; i<=n; i++)
        scanf("%lf%lf", x+i, y+i);
    char op[5];
    int u, v;
    while(~scanf("%s", op))
    {
        if(op[0]=='O')
        {
            scanf("%d", &u);
            ok[u]=true;
            for(int i=1; i<=n; i++)
                if(i!=u && ok[i])
                    if(dis(u, i)<=d)
                    {
                        u=find(u), v=find(i);
                        f[v]=u;
                    }
        }
        else
        {
            scanf("%d%d", &u, &v);
            u=find(u), v=find(v);
            if(u==v)
                puts("SUCCESS");
            else puts("FAIL");
        }
    }
    return 0;
}
