#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <set>
#include <algorithm>
using namespace std;
const int maxn=110;

int n, scc_cnt, col[maxn], pre[maxn][maxn];
set<int> scc[maxn][3];
bool g[maxn][maxn], d[maxn][maxn];
vector<int> G[maxn], ans[3];

void init()
{
    scc_cnt=0;
    memset(g, 0, sizeof g);
    memset(col, 0, sizeof col);
    memset(d, 0, sizeof d);
    ans[0].clear();
    ans[1].clear();
    for(int i=0; i<=n; i++)
    {
        scc[i][0].clear();
        scc[i][1].clear();
        G[i].clear();
    }
}

bool dfs(int u)
{
    for(int i=0; i<G[u].size(); i++)
    {
        int v=G[u][i];
        if(col[u]==col[v])return false;
        if(!col[v])
        {
            col[v]=3-col[u];
            scc[scc_cnt][col[v]-1].insert(v);
            if(!dfs(v))return false;
        }
    }
    return true;
}

bool build()
{
    for(int i=1; i<=n; i++)
    {
        int x;
        while(scanf("%d", &x) && x)
            g[i][x]=true;
    }
    for(int i=1; i<=n; i++)
        for(int j=i+1; j<=n; j++)
            if(!g[i][j] || !g[j][i])
            {
                G[i].push_back(j);
                G[j].push_back(i);
            }
    for(int i=1; i<=n; i++)if(!col[i])
        {
            col[i]=1;
            scc[++scc_cnt][0].insert(i);
            if(!dfs(i))return false;
        }
    return true;
}

int dp()
{
    d[0][0]=1;
    for(int i=1; i<=scc_cnt; i++)
        for(int j=0; j<=(n>>1); j++)
        {
            int x=j-scc[i][0].size();
            if(x>=0 && d[i-1][x])
            {
                d[i][j]=true;
                pre[i][j]=0;
            }
            x=j-scc[i][1].size();
            if(x>=0 && d[i-1][x])
            {
                d[i][j]=true;
                pre[i][j]=1;
            }
        }
    for(int i=(n>>1); i; i--)
        if(d[scc_cnt][i])
            return i;
}

void dfs2(int c, int x)
{
    if(c==0)return ;
    if(pre[c][x]==0)
    {
        for(set<int>::iterator i=scc[c][0].begin(); i!=scc[c][0].end(); i++)
            ans[0].push_back(*i);
        for(set<int>::iterator i=scc[c][1].begin(); i!=scc[c][1].end(); i++)
            ans[1].push_back(*i);
        dfs2(c-1, x-scc[c][0].size());
    }
    else
    {
        for(set<int>::iterator i=scc[c][1].begin(); i!=scc[c][1].end(); i++)
            ans[0].push_back(*i);
        for(set<int>::iterator i=scc[c][0].begin(); i!=scc[c][0].end(); i++)
            ans[1].push_back(*i);
        dfs2(c-1, x-scc[c][1].size());
    }
}

int main()
{
    int T;
    scanf("%d", &T);
    while(T--)
    {
        scanf("%d", &n);
        init();
        if(!build())
            puts("No solution");
        else
        {
            int k=dp();
            dfs2(scc_cnt, k);
            for(int i=0; i<2; i++)
            {
                printf("%d", ans[i].size());
                for(int j=0; j<ans[i].size(); j++)
                    printf(" %d", ans[i][j]);
                puts("");
            }
        }
        if(T)puts("");
    }
    return 0;
}
