#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;
typedef long long LL;
const int maxn=2200;
const LL oo=0x3f3f3f3f3f3f3f3f;
int n, m;
LL a[maxn], to[maxn];
LL d[2][maxn][2];

LL dp()
{
    int cur=1, pre=0;
    for(int i=0; i<m; i++)
        d[pre][i][0]=d[pre][i][1]=abs(a[0]-to[i]);
    for(int i=1; i<n; i++)
    {
        LL t=oo;
        memset(d[cur], 0x3f, sizeof d[cur]);
        for(int j=0; j<m; j++)
        {
            t=min(t, d[pre][j][0]);
            d[cur][j][0]=min(d[cur][j][0], t+abs(a[i]-to[j]));
        }
        t=oo;
        for(int j=m-1; j>=0; j--)
        {
            t=min(t, d[pre][j][1]);
            d[cur][j][1]=min(d[cur][j][1], t+abs(a[i]-to[j]));
        }
        swap(cur, pre);
    }
    LL ans=oo;
    for(int i=0; i<m; i++)
        ans=min(ans, min(d[pre][i][0], d[pre][i][1]));
    return ans;
}

int main()
{
    scanf("%d", &n);
    for(int i=0; i<n; i++)
    {
        scanf("%I64d", a+i);
        to[i]=a[i];
    }
    sort(to, to+n);
    m=unique(to, to+n)-to;
    printf("%I64d\n", dp());
    return 0;
}
