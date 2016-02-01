#include <cstdio>
#include <algorithm>
using namespace std;
typedef long long LL;
const int maxn=1000000+10;
const LL oo=0x3f3f3f3f3f3f3f3f;

int m, n, a[maxn];
LL d[2][maxn];

int main()
{
    while(~scanf("%d%d", &m, &n))
    {
        for(int i=1; i<=n; i++)
            scanf("%d", a+i);
        int cur=1, pre=0;
        for(int i=1; i<=n; i++)
            d[pre][i]=max((LL)a[i], a[i]+d[pre][i-1]);
        for(int i=2; i<=m; i++)
        {
            LL t=d[pre][i-1];
            for(int j=i; j<=n; j++)
            {
                d[cur][j]=t+a[j];
                if(j-1>=i)
                    d[cur][j]=max(d[cur][j], d[cur][j-1]+a[j]);
                t=max(t, d[pre][j]);
            }
            swap(cur, pre);
        }
        LL ans=-oo;
        for(int i=m; i<=n; i++)
            ans=max(ans, d[pre][i]);
        printf("%d\n", ans);
    }
    return 0;
}
