#include <cstdio>
#include <cstring>
using namespace std;
typedef long long LL;

long long n, d[30][11];
int num[30], cnt;

LL dp(int i, int s, bool e)
{
    if(i==-1)return s==10;
    if(!e && ~d[i][s])return d[i][s];
    int u=e?num[i]:9;
    LL ans=0;
    for(int j=0; j<=u; j++)
    {
        int t;
        if(s==10)t=10;
        else t=j;
        if(s==4 && j==9)t=10;
        ans+=dp(i-1, t, e&&j==u);
    }
    return e?ans:d[i][s]=ans;
}
int main()
{
    int T;
    scanf("%d", &T);
    while(T--)
    {
        scanf("%I64d", &n);
        cnt=0;
        while(n)
        {
            num[cnt++]=n%10;
            n/=10;
        }
        memset(d, -1, sizeof d);
        printf("%I64d\n", dp(cnt-1, 0, 1));
    }
    return 0;
}
