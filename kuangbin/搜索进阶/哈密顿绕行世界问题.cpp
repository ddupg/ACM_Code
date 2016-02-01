#include <iostream>
#include <cstring>
#include <cstdio>
using namespace std;

int g[22][5];
int ans[22], kase=0, start;
int vis[25]= {0};
void dfs(int u, int d)
{
    if(d>20 && u==start)
    {
        printf("%d: ", ++kase);
        for(int i=1; i<=21; i++)
            printf(" %d", ans[i]);
        puts("");
        return ;
    }
    for(int i=0; i<3; i++)
        if(!vis[g[u][i]])
        {
            vis[g[u][i]]=1;
            ans[d+1]=g[u][i];
            dfs(g[u][i], d+1);
            vis[g[u][i]]=0;
        }
}

int main()
{
    while(~scanf("%d", &g[1][0]) && g[1][0])
    {
        memset(vis, 0, sizeof(vis));
        scanf("%d%d", &g[1][1], &g[1][2]);
        for(int i=2; i<=20; i++)
            for(int j=0; j<3; j++)
                scanf("%d", &g[i][j]);
        scanf("%d", &start);
        ans[1]=start;
        dfs(start, 1);
    }
    return 0;
}
