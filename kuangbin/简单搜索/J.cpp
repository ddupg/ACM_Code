#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <queue>
#define mem(a, val) memset((a), (val), sizeof(a))
const int maxn=2110;
char s[maxn][maxn];
int vis[maxn][maxn], go[maxn][maxn];
int n, m;
int dx[]={0, 0, 1, -1};
int dy[]={1, -1, 0, 0};
struct Node
{
    int x, y;
    Node(int x=0, int y=0):x(x), y(y){}
}q[maxn*maxn], S;
bool inside(int x, int y)
{
    return x>=0 && x<m && y>=0 && y<n;
}

void init()
{
    for(int i=0; i<m; i++)
        for(int j=0; j<n; j++)
            vis[i][j]=go[i][j]=-1;
}

void fire(int x, int y)
{
    int head=0, tail=0;
    q[tail++]=Node(x, y);
    vis[x][y]=0;
    while(head<tail)
    {
        Node t=q[head++];
        for(int i=0; i<4; i++)
        {
            int nx=t.x+dx[i], ny=t.y+dy[i];
            if(inside(nx, ny) && s[nx][ny]!='#' && (vis[nx][ny]==-1 || vis[nx][ny]>vis[t.x][t.y]+1))
            {
                vis[nx][ny]=vis[t.x][t.y]+1;
                q[tail++]=Node(nx, ny);
            }
        }
    }
}

int bfs()
{
    int head=0, tail=0;
    q[tail++]=S;
    go[S.x][S.y]=0;
    while(head<tail)
    {
        Node t=q[head++];
        for(int i=0; i<4; i++)
        {
            int nx=t.x+dx[i], ny=t.y+dy[i];
            if(!inside(nx, ny))
                return go[t.x][t.y]+1;
            else if(s[nx][ny]!='#' && go[nx][ny]==-1 && (go[t.x][t.y]+1<vis[nx][ny] || vis[nx][ny]==-1) )
            {
                go[nx][ny]=go[t.x][t.y]+1;
                q[tail++]=Node(nx, ny);
            }
        }
    }
    return -1;
}

int main()
{
    int kase;
    scanf("%d", &kase);
    while(kase--)
    {
        scanf("%d%d", &m, &n);
        init();
        for(int i=0; i<m; i++)
            scanf("%s", s[i]);
        for(int i=0; i<m; i++)
            for(int j=0; j<n; j++)
            {
                if(s[i][j]=='F')
                    fire(i, j);
                if(s[i][j]=='J')
                    S=Node(i, j);
            }
        int ans=bfs();
        if(~ans)
            printf("%d\n", ans);
        else puts("IMPOSSIBLE");
    }
    return 0;
}
