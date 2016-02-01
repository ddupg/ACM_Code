#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cstring>
using namespace std;
const int maxn=1110;
int n, root, cnt[maxn], c[maxn], pre[maxn], vis[maxn];

int find()
{
    double Max=0;
    int ans;
    for(int i=1; i<=n; i++)
        if(i!=root && !vis[i] && (double)c[i]/cnt[i]>Max)
            Max=(double)c[ans=i]/cnt[i];
    return ans;
}

int solve()
{
    int ans=0;
    for(int run=0; run<n-1; run++)
    {
        int k=find();
        vis[k]=true;
        int p=pre[k];
        while(vis[p])
            p=pre[p];
        ans+=cnt[p]*c[k];
        cnt[p]+=cnt[k];
        c[p]+=c[k];
    }
    return ans+c[root];
}

int main()
{
    while(~scanf("%d%d", &n, &root) && n+root)
    {
        memset(vis, 0, sizeof(vis));
        for(int i=1; i<=n; i++)
            cnt[i]=scanf("%d", c+i);
        for(int i=0; i<n-1; i++)
        {
            int u, v;
            scanf("%d%d", &u, &v);
            pre[v]=u;
        }
        printf("%d\n", solve());
    }
    return 0;
}
