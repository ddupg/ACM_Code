#include <iostream>
#include <cstdio>
#include <queue>
using namespace std;
typedef long long LL;
typedef unsigned long long LLU;

queue<int> q;
int n, e=0, cnt[1<<17], sum[1<<17];

int main()
{
    scanf("%d", &n);
    for(int i=0; i<n; i++)
    {
        scanf("%d%d", cnt+i, sum+i);
        e+=cnt[i];
        if(cnt[i]==1)
            q.push(i);
    }
    printf("%d\n", e>>1);
    while(!q.empty())
    {
        int x=q.front();
        q.pop();
        if(!cnt[x])continue ;
        int pre=sum[x];
        printf("%d %d\n", x, pre);
        sum[pre]^=x;
        if(--cnt[pre]==1)
            q.push(pre);
    }
    return 0;
}
