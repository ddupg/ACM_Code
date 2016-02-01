#include <cstdio>
#include <cstring>
using namespace std;

int d[15][5000], num[15], a, b;

int f(int x)
{
    int ans=0;
    for(int b=1; x; b<<=1, x/=10)
        ans+=x%10*b;
    return ans;
}

int dfs(int i, int s, bool e)
{
    if(i==-1)return s>=0;
    if(s<0)return 0;
    if(!e && ~d[i][s])return d[i][s];
    int u=e?num[i]:9;
    int ans=0;
    for(int j=0; j<=u; j++)
        ans+=dfs(i-1, s-j*(1<<i), e&&j==u);
    return e?ans:d[i][s]=ans;
}

int cal(int x)
{
    int i;
    for(i=0; x; i++, x/=10)
        num[i]=x%10;
    return dfs(i-1, f(a), true);
}

int main()
{
    int T, kase=0;
    memset(d, -1, sizeof d);
    scanf("%d", &T);
    while(T--)
    {
        scanf("%d%d", &a, &b);
        printf("Case #%d: %d\n", ++kase, cal(b));
    }
    return 0;
}
