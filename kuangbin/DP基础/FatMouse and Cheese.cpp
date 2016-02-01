#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

int n, k, d[110][110], g[110][110];
int dx[]= {0, 0, -1, 1};
int dy[]= {1, -1, 0, 0};

bool inside(int x, int y)
{
    return x>=0 && y>=0 && x<n && y<n;
}

int dp(int x, int y)
{
    if(~d[x][y])return d[x][y];
    d[x][y]=g[x][y];
    for(int i=0; i<4; i++)
        for(int j=1; j<=k; j++)
        {
            int nx=x+dx[i]*j, ny=y+dy[i]*j;
            if(inside(nx, ny) && g[nx][ny]>g[x][y])
                d[x][y]=max(d[x][y], dp(nx, ny)+g[x][y]);
        }
    return d[x][y];
}

int main()
{
    while(~scanf("%d%d", &n, &k))
    {
        if(n==-1 && k==-1)break;
        int cnt=0;
        for(int i=0; i<n; i++)
            for(int j=0; j<n; j++)
                scanf("%d", &g[i][j]);
        memset(d, -1, sizeof d);
        printf("%d\n", dp(0, 0));
    }
    return 0;
}
