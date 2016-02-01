#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int oo=0x3f3f3f3f;

int d[110][3300], mod[10][110];
int val[]= {6, 2, 5, 5, 4, 5, 6, 3, 7, 6};
int n, m;

void init()
{
    memset(mod, 0, sizeof mod);
    for(int i=1; i<=9; i++)
    {
        mod[i][1]=i%m;
        for(int j=2; j<=100; j++)
            mod[i][j]=mod[i][j-1]*10%m;
    }
}

int dp()
{
    memset(d, 0x3f, sizeof d);
    d[0][0]=0;
    for(int i=0; i<=9; i++)
        d[1][i%m]=min(val[i], d[1][i%m]);
    for(int i=1; i<n/2; i++)
        for(int j=0; j<m; j++)
            if(d[i][j]<=n)
            {
                for(int k=0; k<=9; k++)
                    d[i+1][(j*10+k)%m]=min(d[i][j]+val[k], d[i+1][(j*10+k)%m]);
            }
    for(int i=n/2; i; i--)
        if(d[i][0]<=n)
            return i;
    return -1;
}

void dfs(int pos, int x, int sum)
{
    if(pos==0)
        return ;
    for(int i=9; i>=0; i--)
        for(int t=0; t<m; t++)
            if((t+mod[i][pos])%m==x)
            {
                if(val[i]+d[pos-1][t]<=sum)
                {
                    printf("%d", i);
                    dfs(pos-1, t, sum-val[i]);
                    return ;
                }
            }
}

int main()
{
    int kase=0;
    while(~scanf("%d", &n) && n)
    {
        scanf("%d", &m);
        init();
        int len=dp();
        printf("Case %d: ", ++kase);
        if(len==-1)
            printf("-1");
        else
        {
            for(int i=9; i>=0; i--)
                if(val[i]+d[len-1][(m-mod[i][len])%m]<=n)
                {
                    printf("%d", i);
                    dfs(len-1, (m-mod[i][len])%m, n-val[i]);
                    break;
                }
        }
        puts("");
    }
    return 0;
}
