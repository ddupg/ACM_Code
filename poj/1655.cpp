#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;
const int maxn=22000;

int n, rt, sz[maxn], num[maxn];
vector<int> G[maxn];

void dfs(int u, int fa)
{
    sz[u]=1;
    num[u]=0;
    for(int i=0; i<G[u].size(); i++)
    {
        int v=G[u][i];
        if(v==fa)continue ;
        dfs(v, u);
        sz[u]+=sz[v];
        num[u]=max(num[u], sz[v]);
    }
    num[u]=max(num[u], n-sz[u]);
    if(rt==-1 || (num[rt]>num[u]) || (num[rt]==num[u] && u<rt))
        rt=u;
}

int main()
{
    int T;
    scanf("%d", &T);
    while(T--)
    {
        scanf("%d", &n);
        for(int i=0; i<=n; i++)
            G[i].clear();
        for(int i=0; i<n-1; i++)
        {
            int u, v;
            scanf("%d%d", &u, &v);
            G[u].push_back(v);
            G[v].push_back(u);
        }
        rt=-1;
        dfs(1, -1);
        printf("%d %d\n", rt, num[rt]);
    }
    return 0;
}
