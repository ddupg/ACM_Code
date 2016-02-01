#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;
const int maxn=100000+10;
typedef long long LL;

int a[maxn];
vector<int> G[maxn];

int main()
{
    int n, m;
    long long ans=0, sum=0;
    scanf("%d%d", &n, &m);
    for(int i=0; i<m; i++)
    {
        scanf("%d", a+i);
        if(i && a[i]!=a[i-1])
        {
            G[a[i]].push_back(a[i-1]);
            G[a[i-1]].push_back(a[i]);
            sum+=abs(a[i]-a[i-1]);
        }
    }
    ans=sum;
    for(int i=1; i<=n; i++)
    {
        vector<int> cur=G[i];
        if(!cur.size())continue ;
        sort(cur.begin(), cur.end());
        int x=cur[cur.size()/2];
        LL ret=sum;
        for(int j=0; j<cur.size(); j++)
            ret=ret-abs(i-cur[j])+abs(x-cur[j]);
        ans=min(ans, ret);
    }
    printf("%I64d\n", ans);
    return 0;
}
