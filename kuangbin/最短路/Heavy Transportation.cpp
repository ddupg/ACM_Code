#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cstring>
#include <vector>
using namespace std;
const int maxn=1100;
struct Edge
{
    int u, v, d;
    Edge(int u, int v, int d):u(u),v(v), d(d){}
    bool operator < (const Edge e)const
    {
        return d>e.d;
    }
};
vector<Edge> edge;
int n, m, f[maxn];

int find(int x)
{
    return x==f[x]?x:f[x]=find(f[x]);
}

int main()
{
    int T, kase=0;
    scanf("%d", &T);
    while(T--)
    {
        edge.clear();
        scanf("%d%d", &n, &m);
        for(int i=1; i<=n; i++)f[i]=i;
        while(m--)
        {
            int u, v, d;
            scanf("%d%d%d", &u, &v, &d);
            edge.push_back(Edge(u, v, d));
        }
        sort(edge.begin(), edge.end());
        int ans;
        for(int i=0; i<edge.size(); i++)
        {
            int u=find(edge[i].u), v=find(edge[i].v);
            if(u==v)continue ;
            ans=edge[i].d;
            f[u]=v;
            if(find(1)==find(n))
                break;
        }
        printf("Scenario #%d:\n%d\n\n", ++kase, ans);
    }
    return 0;
}
