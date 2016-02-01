#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
using namespace std;

int n;
int dx[]={0, 0, 1, -1};
int dy[]={1, -1, 0, 0};
char s[15][15];

bool inside(int x, int y)
{
    return x>=0 && x<n && y>=0 && y<n;
}

void next(int x, int y, int& nx, int& ny)
{
    if(y==n-1)
        nx=x+1, ny=0;
    else nx=x, ny=y+1;
}

bool check(int x, int y)
{
    for(int i=0; i<4; i++)
    {
        int nx=x+dx[i], ny=y+dy[i];
        if(inside(nx, ny))
            if(s[nx][ny]==s[x][y])return false;
    }
    return true;
}

bool dfs(int x, int y)
{
    if(!inside(x, y))return true;
    int nx, ny;
    next(x, y, nx, ny);
    if(s[x][y]!='.')
        return dfs(nx, ny);
    for(int i=0; i<26; i++)
    {
        s[x][y]='A'+i;
        if(check(x, y) && dfs(nx, ny))
            return true;
    }
    return false;
}

int main()
{
    int T, kase=0;
    scanf("%d", &T);
    while(T--)
    {
        scanf("%d", &n);
        for(int i=0; i<n; i++)
            scanf("%s", s[i]);

        dfs(0, 0);
        printf("Case %d:\n", ++kase);
        for(int i=0; i<n; i++)
            puts(s[i]);
    }
    return 0;
}
