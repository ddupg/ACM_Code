#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <queue>
#include <vector>
using namespace std;
const int maxn=220;
const int INF=1e9;
int n, k[maxn];

int spfa(int s, int t)
{
    queue<int> q;
    int vis[maxn]={0}, d[maxn];
    for(int i=1; i<=n; i++)
        d[i]=i==s?0:INF;
    q.push(s);
    vis[s]=1;
    while(!q.empty())
    {
        int u=q.front();
        q.pop();
        vis[u]=0;
        if(u+k[u]<=n && d[u+k[u]]>d[u]+1)
        {
            d[u+k[u]]=d[u]+1;
            if(!vis[u+k[u]])
                q.push(u+k[u]);
        }
        if(u-k[u]>0 && d[u-k[u]]>d[u]+1)
        {
            d[u-k[u]]=d[u]+1;
            if(!vis[u-k[u]])
                q.push(u-k[u]);
        }
    }
    return d[t]>=INF?-1:d[t];
}

int main()
{
    int s, t;
    while(~scanf("%d", &n) && n)
    {
        scanf("%d%d", &s, &t);
        for(int i=1; i<=n; i++)
            scanf("%d", k+i);
        printf("%d\n", spfa(s, t));
    }
    return 0;
}
