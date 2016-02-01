#include <cstdio>
#include <cstring>
using namespace std;
typedef long long LL;
LL d[30][1<<10][10];
int num[30], k, news[10][1<<10];

int getnews(int x, int s)
{
    for(int i=x; i<10; i++)
        if(1<<i&s)return s^(1<<i)|(1<<x);
    return s|(1<<x);
}

void init()
{
    for(int i=0; i<10; i++)
        for(int j=0; j<(1<<10); j++)
            news[i][j]=getnews(i, j);
}

LL dfs(int i, int s, bool first, bool e)
{
    if(i==-1)return __builtin_popcount(s)==k;
    if(!e && ~d[i][s][k])return d[i][s][k];
    int u=e?num[i]:9;
    LL ans=0;
    for(int j=0; j<=u; j++)
        ans+=dfs(i-1, first&&j==0?0:news[j][s], first&&j==0, e&&j==u);
    return e?ans:d[i][s][k]=ans;
}

LL cal(LL x)
{
    int i, cnt=0;
    for(i=0; x; i++, x/=10)
        num[i]=x%10;
    return dfs(i-1, 0, 1, 1);
}

int main()
{
    init();
    int T, kase=0;
    scanf("%d", &T);
    memset(d, -1, sizeof d);
    while(T--)
    {
        LL a, b;
        scanf("%I64d %I64d %d", &a, &b, &k);
        printf("Case #%d: %I64d\n", ++kase, cal(b)-cal(a-1));
    }
    return 0;
}
