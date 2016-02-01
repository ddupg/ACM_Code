#include <cstdio>
#include <cstring>
using namespace std;
typedef long long LL;

int d[12][82][82][82], num[12];

int dfs(int i, int s, int sum, int m, bool e)
{
    if(i==-1)return s==0 && sum==m;
    if(!e && ~d[i][s][sum][m])return d[i][s][sum][m];
    if(sum>m)return 0;
    int u=e?num[i]:9, ans=0;
    for(int j=0; j<=u; j++)
        ans+=dfs(i-1, (s*10+j)%m, sum+j, m, e&&j==u);
    return e?ans:d[i][s][sum][m]=ans;
}

int cal(int x)
{
    int cnt=0, ans=0;
    for(; x; cnt++, x/=10)
        num[cnt]=x%10;
    for(int i=1; i<82; i++)
        ans+=dfs(cnt-1, 0, 0, i, true);
    return ans;
}

int main()
{
    int T, a, b, kase=0;
    scanf("%d", &T);
    memset(d, -1, sizeof d);
    while(T--)
    {
        scanf("%d%d", &a, &b);
        printf("Case %d: %d\n", ++kase, cal(b)-cal(a-1));
    }
    return 0;
}
