#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <cstring>
#include <string>
#include <vector>
using namespace std;
typedef long long LL;
typedef unsigned long long LLU;
const int maxn=10000+100;

double p[150][150], d[maxn][150];
int ch[maxn], n, N, m;

void dp()
{
    memset(d, 0, sizeof(d));

    for(int i=0; i<n; i++)
        d[0][i]=1;

    for(int i=0; i<m; i++)
        for(int j=0; j<n; j++)
        {
            d[i+1][j]=max(d[i+1][j], d[i][j]*p[j][ch[i+1]]);
            d[i+1][ch[i+1]]=max(d[i+1][ch[i+1]], d[i][j]*p[j][ch[i+1]]);
        }
}

int main()
{
    while(~scanf("%d", &N))
    {
        n=N*(N-1)*(N-2)/6;
        for(int i=0; i<n; i++)
            for(int j=0; j<n; j++)
                scanf("%lf", &p[i][j]);
        scanf("%d", &m);
        for(int i=1; i<=m; i++)
            scanf("%d", &ch[i]);

        dp();
        double ans=0;
        for(int i=0; i<n; i++)
            ans=max(ans, d[m][i]);
        printf("%lf\n", ans);
    }
    return 0;
}
