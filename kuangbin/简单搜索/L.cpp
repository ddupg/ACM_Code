#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <queue>
#define mem(a, val) memset((a), (val), sizeof(a))

int m, n, vis[110][110];
char s[110][110];
int dx[]= {0, 0, 1, -1, -1, 1, -1, 1};
int dy[]= {1, -1, 0, 0, -1, 1, 1, -1};

int inside(int x, int y)
{
    return x>=0 && x<m && y>=0 && y<n;
}

void dfs(int x, int y)
{
    vis[x][y]=1;
    for(int i=0; i<8; i++)
    {
        int nx=x+dx[i], ny=y+dy[i];
        if(inside(nx, ny) && !vis[nx][ny] && s[nx][ny]=='@')
            dfs(nx, ny);
    }
}

int main()
{
    while(~scanf("%d%d", &m, &n) && n+m)
    {
        int ans=0;
        for(int i=0; i<m; i++)
            scanf("%s", s[i]);
        mem(vis, 0);
        for(int i=0; i<m; i++)
            for(int j=0; j<n; j++)
                if(!vis[i][j] && s[i][j]=='@')
                {
                    ans++;
                    dfs(i, j);
                }
        printf("%d\n", ans);
    }
    return 0;
}
