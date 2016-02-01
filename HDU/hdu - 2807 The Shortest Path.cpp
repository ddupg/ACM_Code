#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn=85;
const int INF=1e8;
int d[maxn][maxn], n, M;

struct Matrix
{
    int m[maxn][maxn];
} mat[maxn];
bool judge(int x, int y, int z)
{
    for(int i=1; i<=M; i++)
        for(int j=1; j<=M; j++)
        {
            int tmp=0;
            for(int k=1; k<=M; k++)
                tmp+=mat[x].m[i][k]*mat[y].m[k][j];
            if(tmp!=mat[z].m[i][j])
                return 0;
        }
    return 1;
}

void init()
{
    for(int i=1; i<=n; i++)
        for(int j=i; j<=n; j++)
            d[i][j]=i==j?0:INF;
}

void floyd()
{
    for(int k=1; k<=n; k++)
        for(int i=1; i<=n; i++)
            for(int j=1; j<=n; j++)
                d[i][j]=min(d[i][j], d[i][k]+d[k][j]);
}

int main()
{
    int q;
    while(~scanf("%d%d", &n, &M) && n+M)
    {
        init();
        for(int i=1; i<=n; i++)
            for(int j=1; j<=M; j++)
                for(int k=1; k<=M; k++)
                    scanf("%d", &mat[i].m[j][k]);
        for(int i=1; i<=n; i++)
            for(int j=1; j<=n; j++)if(i!=j)
                for(int k=1; k<=n; k++)if(i!=k && j!=k)
                    if(judge(i, j, k))
                        d[i][k]=1;
        floyd();
        scanf("%d", &q);
        while(q--)
        {
            int u, v;
            scanf("%d%d", &u, &v);
            if(d[u][v]>=INF)
                puts("Sorry");
            else printf("%d\n", d[u][v]);
        }
    }
    return 0;
}
