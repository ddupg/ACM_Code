#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;
const int maxn=1010;

struct Node
{
    int like, hate;
    Node(int l=0, int h=0):like(l), hate(h) {}
} nd[maxn];
vector<int> G[maxn];

void init()
{
    for(int i=0; i<maxn; i++)
        G[i].clear();
}

int n, link[maxn];
bool used[maxn];

bool dfs(int u)
{
    for(int i=0; i<G[u].size(); i++)
    {
        int v=G[u][i];
        if(!used[v])
        {
            used[v]=true;
            if(link[v]==-1 || dfs(link[v]))
            {
                link[v]=u;
                return true;
            }
        }
    }
    return false;
}

int hungary(int n)
{
    int ans=0;
    memset(link, -1, sizeof link);
    for(int u=1; u<=n; u++)
    {
        memset(used, 0, sizeof used);
        ans+=dfs(u);
    }
    return ans;
}

int main()
{
    int n, m, p;
    while(~scanf("%d%d%d", &n, &m, &p))
    {
        init();
        char c1, c2;
        int ani1, ani2;
        for(int i=1; i<=p; i++)
        {
            scanf("%*c%c%d %c%d", &c1, &ani1, &c2, &ani2);
            nd[i]=Node(c1=='C'?ani1:ani1+n, c2=='C'?ani2:ani2+n);
        }
        for(int i=1; i<=p; i++)
            for(int j=1; j<=p; j++)if(i!=j)
                if(nd[i].like==nd[j].hate || nd[i].hate==nd[j].like)
                    G[i].push_back(j);
        printf("%d\n", p-hungary(p)/2);
    }
    return 0;
}
