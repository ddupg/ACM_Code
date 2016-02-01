#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn=110;
int n, m, d[maxn][maxn];

int main()
{
    while(~scanf("%d%d", &n, &m))
    {
        for(int i=1; i<=n; i++)
            for(int j=1; j<=n; j++)
                d[i][j]=i==j;
        while(m--)
        {
            int u, v;
            scanf("%d%d", &u, &v);
            d[u][v]=1;
        }
        for(int k=1; k<=n; k++)
            for(int i=1; i<=n; i++)
                for(int j=1; j<=n; j++)
                    d[i][j]=d[i][j] || (d[i][k] && d[k][j]);
        int cnt=0;
        for(int i=1; i<=n; i++)
        {
            int flag=1;
            for(int j=1; j<=n; j++)
                if(!d[i][j] && !d[j][i])
                    flag=0;
            cnt+=flag;
        }
        printf("%d\n", cnt);
    }
    return 0;
}
