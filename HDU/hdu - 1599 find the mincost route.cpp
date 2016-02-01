#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
const int maxn=110;
const int INF=1e8;
int w[maxn][maxn], d[maxn][maxn], n, m;

int floyd(int& ans)
{
    for(int k=1; k<=n; k++)
    {
        for(int i=1; i<k; i++)
            for(int j=1; j<i; j++)
                ans=min(ans, d[i][j]+w[j][k]+w[k][i]);
        for(int i=1; i<=n; i++)
            for(int j=1; j<=n; j++)
                d[i][j]=min(d[i][j], d[i][k]+d[k][j]);
    }
}

int main()
{
    while(~scanf("%d%d", &n, &m))
    {
        for(int i=1; i<=n; i++)
            for(int j=1; j<=n; j++)
                d[i][j]=d[j][i]=w[i][j]=w[j][i]=i==j?0:INF;
        while(m--)
        {
            int u, v, dis;
            scanf("%d%d%d", &u, &v, &dis);
            w[u][v]=w[v][u]=d[u][v]=d[v][u]=min(w[u][v], dis);
        }
        int ans=INF;
        floyd(ans);
        if(ans>=INF)
            puts("It's impossible.");
        else printf("%d\n", ans);
    }
    return 0;
}
