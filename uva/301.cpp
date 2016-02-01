#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <set>
#include <vector>
using namespace std;

int limit, n, m, cnt[10], ans;

struct Node
{
    int s, t, num;
} nd[30];

void dfs(int x, int sum)
{
    if(x==m)
    {
        ans=max(ans, sum);
        return ;
    }
    int s=0;
    for(int i=x; i<m; i++)
        s+=(nd[i].t-nd[i].s)*nd[i].num;
    if(sum+s<=ans)return ;
    bool flag=true;
    for(int i=nd[x].s+1; i<=nd[x].t; i++)
        if((cnt[i]+=nd[x].num)>limit)
            flag=false;
    if(flag)
        dfs(x+1, sum+(nd[x].t-nd[x].s)*nd[x].num);
    for(int i=nd[x].s+1; i<=nd[x].t; i++)
        cnt[i]-=nd[x].num;
    dfs(x+1, sum);
}

int main()
{
    while(~scanf("%d%d%d", &limit, &n, &m) && limit)
    {
        for(int i=0; i<m; i++)
            scanf("%d%d%d", &nd[i].s, &nd[i].t, &nd[i].num);
        memset(cnt, 0, sizeof cnt);
        ans=0;
        dfs(0, 0);
        printf("%d\n", ans);
    }
    return 0;
}
