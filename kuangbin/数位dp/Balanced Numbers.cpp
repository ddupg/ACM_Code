#include <iostream>
#include <cstring>
using namespace std;
typedef long long LL;

LL d[21][1<<10][1<<10];
int num[21], cnt;

bool judge(int s, int x)
{
    for(int i=0; i<10; i++)
        if(1<<i&s)
        {
            if((i&1) && (1<<i&x))return false;
            if(!(i&1) && !(1<<i&x))return false;
        }
    return true;
}

LL dfs(int i, int s, int x, int e, int first)
{
    if(i==-1)return judge(s, x);
    if(!e && ~d[i][s][x])return d[i][s][x];
    int u=e?num[i]:9;
    LL ans=0;
    for(int j=0; j<=u; j++)
    {
        int news=s, newx=x;
        if(!first||j)news|=(1<<j), newx^=(1<<j);
        ans+=dfs(i-1, news, newx, e&&j==u, first&&j==0);
    }
    return e?ans:d[i][s][x]=ans;
}

LL cal(LL x)
{
    for(cnt=0; x; x/=10, cnt++)
        num[cnt]=x%10;
    return dfs(cnt-1, 0, 0, 1, 1);
}

int main()
{
    int T;
    LL a, b;
    cin>>T;
    memset(d, -1, sizeof d);
    while(T--)
    {
        cin>>a>>b;
        cout<<cal(b)-cal(a-1)<<endl;
    }
    return 0;
}
