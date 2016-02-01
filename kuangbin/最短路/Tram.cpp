#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;

int d[110][110];

int main()
{
    int n, s, t;
    while(~scanf("%d%d%d", &n, &s, &t))
    {
        memset(d, 0x3f, sizeof d);
        for(int i=1; i<=n; i++)
        {
            d[i][i]=0;
            int k, v;
            scanf("%d", &k);
            for(int j=0; j<k; j++)
            {
                scanf("%d", &v);
                d[i][v]=j?1:0;
            }
        }
        for(int k=1; k<=n; k++)
            for(int i=1; i<=n; i++)
                for(int j=1; j<=n; j++)
                    d[i][j]=min(d[i][j], d[i][k]+d[k][j]);
        printf("%d\n", d[s][t]==0x3f3f3f3f?-1:d[s][t]);
    }
    return 0;
}
