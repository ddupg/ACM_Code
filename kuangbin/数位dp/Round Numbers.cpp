#include <iostream>
#include <cstring>
using namespace std;
typedef long long LL;

LL d[50][50][50];
int num[50], cnt;

LL dfs(int i, int p, int s, bool e, bool first)
{
    if(i==-1)return s<=(p+1>>1);
    if(!e && ~d[i][p][s])return d[i][p][s];
    int u=e?num[i]:1;
    LL ans=0;
    for(int j=0; j<=u; j++)
        ans+=dfs(i-1, (first&&j)?i:p, first?j:s+j, e&&j==u, first&&j==0);
    return e?ans:d[i][p][s]=ans;
}

LL cal(LL x)
{
    cnt=0;
    for(; x;x>>=1)
        num[cnt++]=x&1;
    memset(d, -1, sizeof d);
    return dfs(cnt-1, 0, 0, 1, 1);
}

int main()
{
    LL a, b;
    while(cin>>a>>b)
        cout<<cal(b)-cal(a-1)<<endl;
    return 0;
}
