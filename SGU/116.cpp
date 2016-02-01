#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>
using namespace std;
const int maxn=10010;
const int oo=0x3f3f3f3f;

bool vis[maxn];
vector<int> sp, ans;
int pre[maxn+100], dp[maxn];

void init()
{
    for(int i=2; i*i<maxn; i++)
        for(int j=i*i; j<maxn; j+=i)
            vis[j]=true;
    int cnt=1;
    for(int i=3; i<maxn; i++)
        if(!vis[i])
        {
            cnt++;
            if(!vis[cnt])
                sp.push_back(i);
        }
}

int DP(int x)
{
    if(x==0)return dp[x]=0;
    if(~dp[x])return dp[x];
    dp[x]=oo;
    for(int i=0; i<sp.size() && sp[i]<=x; i++)
        if(vis[x-sp[i]] && dp[x]>DP(x-sp[i]))
        {
            dp[x]=dp[x-sp[i]]+1;
            pre[x]=sp[i];
        }
    return dp[x];

}
int main()
{
    init();
    int n;
    cin>>n;
    memset(vis, 0, sizeof vis);
    vis[0]=true;
    for(int i=1; i<=n; i++)
        for(int j=sp.size()-1; j>=0; j--)
            if(sp[j]<=i && vis[i-sp[j]])
            {
                vis[i]=true;
                break;
            }
    if(n && vis[n])
    {
        memset(dp, -1, sizeof dp);
        cout<<DP(n)<<endl;
        int t=n;
        while(t)
        {
            ans.push_back(pre[t]);
            t-=pre[t];
        }
        sort(ans.begin(), ans.end());
        for(int i=ans.size()-1; i>0; i--)
            cout<<ans[i]<<' ';
        cout<<ans[0]<<endl;
    }
    else cout<<0<<endl;
    return 0;
}
