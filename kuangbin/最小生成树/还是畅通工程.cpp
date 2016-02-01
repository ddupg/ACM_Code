#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>
#include <cmath>
using namespace std;
const int maxn=110;
struct Edge
{
    int u, v;
    double d;
    Edge(int u, int v, double d):u(u), v(v), d(d){}
    bool operator < (const Edge a)const
    {
        return d<a.d;
    }
};
vector<Edge> edge;
double x[maxn], y[maxn];
int f[maxn], n;
void init()
{
    for(int i=1; i<=n; i++)
        f[i]=i;
}
int find(int x)
{
    return f[x]==x?x:f[x]=find(f[x]);
}

int main()
{
    int T;
    scanf("%d", &T);
    while(T-- && ~scanf("%d", &n) && n)
    {
        init();
        edge.clear();
        for(int i=1; i<=n; i++)
        {
            scanf("%lf%lf", &x[i], &y[i]);
            for(int j=1; j<i; j++)
            {
                double dis=sqrt((x[i]-x[j])*(x[i]-x[j])+(y[i]-y[j])*(y[i]-y[j]));
                if(dis>=10 && dis<=1000)
                    edge.push_back(Edge(i, j, dis*100));
            }
        }
        sort(edge.begin(), edge.end());
        double ans=0;
        int cnt=0;
        for(int i=0; i<edge.size(); i++)
        {
            int u=find(edge[i].u), v=find(edge[i].v);
            if(u!=v)
            {
                f[u]=v;
                ans+=edge[i].d;
                cnt++;
            }
        }
        if(cnt==n-1)
            printf("%.1lf\n", ans);
        else puts("oh!");
    }
    return 0;
}
