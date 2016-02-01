#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;
const int maxn=220;

int n, m;
int color[maxn];
vector<int> G[maxn];

int linker[maxn];
bool used[maxn];

bool dfs(int u)
{
    for(int i = 0; i < G[u].size(); i++)
        if(!used[G[u][i]])
        {
            int v=G[u][i];
            used[v] = true;
            if(linker[v] == -1 || dfs(linker[v]))
            {
                linker[v] = u;
                return true;
            }
        }
    return false;
}
int hungary()
{
    int res = 0;
    memset(linker,-1,sizeof(linker));
    for(int u = 0; u < n; u++)
    {
        memset(used,false,sizeof(used));
        if(dfs(u))res++;
    }
    return res;
}

bool bipartite(int u)
{
    for(int i=0; i<G[u].size(); i++)
    {
        int v=G[u][i];
        if(color[v]==color[u])return false;
        if(!color[v])
        {
            color[v]=3-color[u];
            if(!bipartite(v))return false;
        }
    }
    return true;
}

int main()
{
    while(~scanf("%d%d", &n, &m))
    {
        memset(color, 0, sizeof color);
        for(int i=0; i<n; i++)
            G[i].clear();
        while(m--)
        {
            int u, v;
            scanf("%d%d", &u, &v);
            u--, v--;
            G[u].push_back(v);
            G[v].push_back(u);
        }
        bool flag=1;
        for(int i=0; i<n && flag; i++)
            if(!color[i])
            {
                color[i]=1;
                flag=bipartite(i);
            }
        if(!flag)
            puts("No");
        else
            printf("%d\n", hungary()>>1);
    }
    return 0;
}
