#include <iostream>
#include <cstring>
using namespace std;
typedef long long LL;
LL d[20][20][2000];
int num[20];

LL dfs(int i, int p, int sum, bool e)
{
    if(i==-1)return !sum;
    if(sum<0)return 0;
    if(!e && ~d[i][p][sum])return d[i][p][sum];
    int u=e?num[i]:9;
    LL ans=0;
    for(int j=0; j<=u; j++)
        ans+=dfs(i-1, p, sum+(i-p)*j, e&&j==u);
    return e?ans:d[i][p][sum]=ans;
}

LL cal(LL x)
{
    if(x<0)return 0;
    int cnt=0;
    for(; x; x/=10, cnt++)
        num[cnt]=x%10;
    LL ans=0;
    for(int i=0; i<cnt; i++)
        ans+=dfs(cnt-1, i, 0, true);
    return ans-cnt+1;
}

int main()
{
    memset(d, -1, sizeof d);
    int T;
    LL a, b;
    cin>>T;
    while(T--)
    {
        cin>>a>>b;
        cout<<cal(b)-cal(a-1)<<endl;
    }
    return 0;
}
