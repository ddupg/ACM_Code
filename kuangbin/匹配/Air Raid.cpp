#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
using namespace std;
const int maxn=550;

int n, m, link[maxn];
bool used[maxn];
vector<int> G[maxn];

bool dfs(int u)
{
    for(int i=0; i<G[u].size(); i++)
    {
        int v=G[u][i];
        if(used[v])continue ;
        used[v]=1;
        if(link[v]==-1 || dfs(link[v]))
        {
            link[v]=u;
            return true;
        }
    }
    return false;
}

int hungary()
{
    memset(link, -1, sizeof link);
    int ans=0;
    for(int u=1; u<=n; u++)
    {
        memset(used, 0, sizeof used);
        ans+=dfs(u);
    }
    return ans;
}

int main()
{
    int T;
    scanf("%d", &T);
    while(T--)
    {
        scanf("%d%d", &n, &m);
        for(int i=1; i<=n; i++)
            G[i].clear();
        while(m--)
        {
            int u, v;
            scanf("%d%d", &u, &v);
            G[u].push_back(v);
        }
        printf("%d\n", n-hungary());
    }
    return 0;
}
