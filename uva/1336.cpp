#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cstring>
using namespace std;
const int maxn=1100;

long long d[maxn][maxn][2], sum, pre[maxn];
int n, v, st;

struct Node
{
    int x, c, d;
    bool operator < (const Node a)const
    {
        return x<a.x;
    }
} nd[maxn], tmp;

int main()
{
    while(~scanf("%d%d%d", &n, &v, &st) && n)
    {
        memset(d, 0x3f, sizeof d);
        nd[n+1].x=st, nd[n+1].c=0, nd[n+1].d=0;
        tmp.x=st, tmp.c=0, tmp.d=0;
        for(int i=1; i<=n; i++)
            scanf("%d%d%d", &nd[i].x, &nd[i].c, &nd[i].d);
        ++n;
        sort(nd+1, nd+n+1);
        sum=0, pre[0]=0;
        for(int i=1; i<=n; i++)
        {
            sum+=nd[i].c;
            pre[i]=pre[i-1]+nd[i].d;
        }
        int k=lower_bound(nd+1, nd+n+1, tmp)-nd;
        d[k][k][0]=d[k][k][1]=0;
        for(int i=k; i; i--)
            for(int j=k; j<=n; j++)
            {
                long long tmp=pre[n]-pre[j]+pre[i-1];
                if(i>1)
                {
                    d[i-1][j][0]=min(d[i-1][j][0],
                                     min(d[i][j][0]+abs(nd[i].x-nd[i-1].x)*tmp,
                                         d[i][j][1]+abs(nd[j].x-nd[i-1].x)*tmp));
                }
                if(j<n)
                {
                    d[i][j+1][1]=min(d[i][j+1][1],
                                     min(d[i][j][0]+abs(nd[j+1].x-nd[i].x)*tmp,
                                         d[i][j][1]+abs(nd[j+1].x-nd[j].x)*tmp));
                }
            }
        printf("%lld\n", min(d[1][n][0], d[1][n][1])/v+sum);
    }
    return 0;
}
