#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn=220;
const int ZERO=400;

int n, m, a[maxn], b[maxn], d[22][1100], pre[22][1100];

bool judge(int i, int j, int k)
{
    while(i && pre[i][j]!=k)
        j=j-a[pre[i][j]]+b[pre[i][j]], i--;
    return !i;
}

int main()
{
    int kase=0;
    while(~scanf("%d%d", &n, &m) && n+m)
    {
        for(int i=1; i<=n; i++)
            scanf("%d%d", a+i, b+i);
        memset(d, -1, sizeof d);
        memset(pre, 0, sizeof pre);
        d[0][ZERO]=0;
        for(int i=0; i<m; i++)
            for(int j=0; j<=2*ZERO; j++)
                if(~d[i][j])
                {
                    for(int k=1; k<=n; k++)
                        if(judge(i, j, k) && d[i][j]+a[k]+b[k]>d[i+1][j+a[k]-b[k]])
                        {
                            d[i+1][j+a[k]-b[k]]=d[i][j]+a[k]+b[k];
                            pre[i+1][j+a[k]-b[k]]=k;
                        }
                }
        int tmp, i;
        for(i=0; d[m][ZERO+i]==-1 && d[m][ZERO-i]==-1; i++)
            ;
        if(d[m][ZERO+i]>d[m][ZERO-i])
            tmp=ZERO+i;
        else tmp=ZERO-i;
        printf("Jury #%d\n", ++kase);
        printf("Best jury has value %d for prosecution and value %d for defence:\n", (tmp-ZERO+d[m][tmp])/2, (d[m][tmp]-tmp+ZERO)/2);

        int ans[22], cnt=0;
        for(int i=m, j=tmp; i; --i, j=j-a[tmp]+b[tmp])
        {
            tmp=pre[i][j];
            ans[cnt++]=tmp;
        }
        sort(ans, ans+cnt);
        for(int i=0; i<m; i++)
            printf(" %d", ans[i]);
        printf("\n\n");
    }
    return 0;
}
