#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef unsigned long long LLU;

LLU d[70][70][120];
int N, K;

LLU dp()
{
    memset(d, 0, sizeof d);
    d[1][1][1%K]=1;
    for(int i=1; i<N; i++)
        for(int j=0; j<=N; j++)
        {
            for(int k=0; k<K; k++)if(d[i][j][k])
            {
                d[i+1][j+1][(k<<1|1)%K]+=d[i][j][k];
                d[i+1][j][(k<<1)%K]+=d[i][j][k];
            }
        }
    return d[N][N>>1][0];
}

int main()
{
    int T, kase=0;
    scanf("%d", &T);
    while(T--)
    {
        scanf("%d%d", &N, &K);
        printf("Case %d: ");
        if(!K || (N&1))
            printf("0\n");
        else printf("%llu\n", ++kase, dp());
    }
    return 0;
}
