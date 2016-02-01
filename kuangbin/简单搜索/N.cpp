#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <queue>
#include <vector>
#include <algorithm>
#define mem(a, val) memset((a), (val), sizeof(a))
using namespace std;
const int maxn=220;
const int INF=1e9;
struct Node
{
    int x, y;
    Node(int x=0, int y=0):x(x), y(y) {}
} q[maxn*maxn];
int m, n, vis[2][maxn][maxn], ans;
int dx[]= {0, 0, -1, 1};
int dy[]= {1, -1, 0, 0};
char s[maxn][maxn];
bool inside(int x, int y)
{
    return x>=0 && x<m && y>=0 && y<n;
}

void bfs(int x, int y)
{
    int flag=s[x][y]=='Y'?0:1;
    mem(vis[flag], -1);
    vis[flag][x][y]=0;
    int head=0, tail=0;
    q[tail++]=Node(x, y);
    int res=0, cnt=0;
    while(head<tail)
    {
        Node t=q[head++];
        for(int i=0; i<4; i++)
        {
            int nx=t.x+dx[i], ny=t.y+dy[i];
            if(inside(nx, ny) && vis[flag][nx][ny]==-1 && s[nx][ny]!='#')
            {
                vis[flag][nx][ny]=vis[flag][t.x][t.y]+1;
                q[tail++]=Node(nx, ny);
            }
        }
    }
}

int main()
{
    while(~scanf("%d%d", &m, &n))
    {
        for(int i=0; i<m; i++)
            scanf("%s", s[i]);
        ans=INF;
        for(int i=0; i<m; i++)
            for(int j=0; j<n; j++)
                if(s[i][j]=='Y' || s[i][j]=='M')
                    bfs(i, j);
        for(int i=0; i<m; i++)
            for(int j=0; j<n; j++)
            {
                if(s[i][j]=='@' && vis[0][i][j]!=-1 && vis[1][i][j]!=-1)
                    ans=min(ans, vis[0][i][j] + vis[1][i][j]);
            }
        printf("%d\n", ans*11);
    }
    return 0;
}
