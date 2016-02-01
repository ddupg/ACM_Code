#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <queue>
#include <algorithm>
#define mem(a, val) memset((a), (val), sizeof(a))
using namespace std;
const int maxn=15;
const int INF=1e9;
int vis[maxn][maxn], m, n, cnt;
char s[maxn][maxn];
int dx[]= {0, 0, 1, -1};
int dy[]= {1, -1, 0, 0};
struct Node
{
    int x, y;
    Node(int x=0, int y=0):x(x), y(y) {}
} point[maxn*maxn], q[maxn*maxn];

bool inside(int x, int y)
{
    return x>=0 && x<m && y>=0 && y<n;
}
int bfs(int a, int b)
{
    mem(vis, -1);
    vis[point[a].x][point[a].y]=0;
    vis[point[b].x][point[b].y]=0;
    int head=0, tail=0;
    q[tail++]=point[a];
    q[tail++]=point[b];
    int num=0, times=0;
    while(head<tail)
    {
        Node t=q[head++];
        num++;
        times=vis[t.x][t.y];
        for(int i=0; i<4; i++)
        {
            int nx=t.x+dx[i], ny=t.y+dy[i];
            if(inside(nx, ny) && vis[nx][ny]==-1 && s[nx][ny]=='#')
            {
                vis[nx][ny]=vis[t.x][t.y]+1;
                q[tail++]=Node(nx, ny);
            }
        }
    }
    return num==cnt?times:INF;
}

int main()
{
    int T, kase=0;
    scanf("%d", &T);
    while(T--)
    {
        scanf("%d%d", &m, &n);
        cnt=0;
        for(int i=0; i<m; i++)
        {
            scanf("%s", s[i]);
            for(int j=0; j<n; j++)
                if(s[i][j]=='#')
                    point[cnt++]=Node(i, j);
        }
        if(cnt<=2)
            printf("Case %d: %d\n", ++kase, 0);
        else
        {
            int ans=INF;
            for(int i=0; i<cnt; i++)
                for(int j=i+1; j<cnt; j++)
                    ans=min(ans, bfs(i, j));
            printf("Case %d: %d\n", ++kase, ans>=INF?-1:ans);
        }
    }
    return 0;
}
