#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn=330;
const int INF=0x3f3f3f3f;
int n, m, Q;
int d[maxn][maxn];
bool mark[maxn];

void init()
{
    for(int i=0; i<n; i++)
        for(int j=i; j<n; j++)
            d[i][j]=d[j][i]=i==j?0:INF;
    memset(mark, 0, sizeof(mark));
}

int main()
{
    int kase=0;
    while(~scanf("%d%d%d", &n, &m, &Q) && n+m+Q)
    {
        init();
        while(m--)
        {
            int u, v, w;
            scanf("%d%d%d", &u, &v, &w);
            d[u][v]=min(d[u][v], w);
        }
        if(kase)puts("");
        printf("Case %d:\n", ++kase);
        while(Q--)
        {
            int op, u, v;
            scanf("%d", &op);
            if(!op)
            {
                scanf("%d", &u);
                if(mark[u])
                    printf("ERROR! At point %d\n", u);
                else
                {
                    mark[u]=1;
                    for(int i=0; i<n; i++)
                        for(int j=0; j<n; j++)
                            d[i][j]=min(d[i][j], d[i][u]+d[u][j]);
                }
            }
            else
            {
                scanf("%d%d", &u, &v);
                if(!mark[u] || !mark[v])
                    printf("ERROR! At path %d to %d\n", u, v);
                else if(d[u][v]<INF)
                    printf("%d\n", d[u][v]);
                else puts("No such path");
            }
        }
    }
    return 0;
}
