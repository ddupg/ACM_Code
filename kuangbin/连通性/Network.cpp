#include <iostream>
#include <sstream>
#include <cstdio>
#include <string>
#include <cstring>
#include <vector>
using namespace std;
const int maxn=110;

int n, dfn, pre[maxn], low[maxn];
bool iscut[maxn], g[maxn][maxn];
vector<int> G[maxn];

void init()
{
    for(int i=0; i<=n; i++)
        G[i].clear();
    memset(iscut, 0, sizeof iscut);
    memset(pre, 0, sizeof pre);
    memset(g, 0, sizeof g);
    dfn=0;
}

int dfs(int u, int fa)
{
    int lowu=pre[u]=++dfn;
    int child=0;
    for(int i=0; i<G[u].size(); i++)
    {
        int v=G[u][i];
        if(!pre[v])
        {
            child++;
            int lowv=dfs(v, u);
            lowu=min(lowu, lowv);
            if(lowv>=pre[u])
                iscut[u]=true;
        }
        else if(pre[v]<pre[u] && v!=fa)
            lowu=min(lowu, pre[v]);
    }
    if(fa<0 && child==1)
        iscut[u]=0;
    return low[u]=lowu;
}

int main()
{
    while(cin>>n && n)
    {
        init();
        string s;
        getchar();
        while(true)
        {
            getline(cin, s);
            if(s=="0")break;
            stringstream ss(s);
            int u, v;
            ss>>u;
            while(ss>>v)
                g[u][v]=g[v][u]=1;
        }
        for(int i=1; i<=n; i++)
            for(int j=1; j<=n; j++)
                if(g[i][j])
                    G[i].push_back(j);
        for(int i=1; i<=n; i++)
            if(!pre[i])
                dfs(i, -1);
        int ans=0;
        for(int i=1; i<=n; i++)
            ans+=iscut[i];
        cout<<ans<<endl;
    }
    return 0;
}
