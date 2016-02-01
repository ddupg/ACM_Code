#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
using namespace std;

int dx[]={0, 0, 1, -1};
int dy[]={1, -1, 0, 0};
char s[2][15][15];
int n, m, t;

struct Node
{
    int f, x, y, d;
    Node(int f, int x, int y, int d):f(f), x(x), y(y), d(d){}
};

bool inside(int x, int y)
{
    return x>=0 && x<n && y>=0 && y<m;
}
bool vis[2][11][11];

bool bfs()
{
    memset(vis, 0, sizeof(vis));
    queue<Node> q;
    q.push(Node(0, 0, 0, 0));
    vis[0][0][0]=1;
    while(!q.empty())
    {
        Node node=q.front();
        q.pop();
        int f=node.f, x=node.x, y=node.y, d=node.d;
        if(s[f][x][y]=='P' && d<=t)return true;
        if(d>t)return false;
        for(int i=0; i<4; i++)
        {
            int nx=x+dx[i], ny=y+dy[i];
            if(!inside(nx, ny) || s[f][nx][ny]=='*')continue ;
            if(s[f][nx][ny]=='#' && !vis[f^1][nx][ny])
            {
                vis[f^1][nx][ny]=1;
                q.push(Node(f^1, nx, ny, d+1));
            }
            if(s[f][nx][ny]!='*' && s[f][nx][ny]!='#' && !vis[f][nx][ny])
            {
                vis[f][nx][ny]=1;
                q.push(Node(f, nx, ny, d+1));
            }
        }
    }
    return false;
}

int main()
{
    int T;
    scanf("%d", &T);
    while(T--)
    {
        scanf("%d%d%d", &n, &m, &t);
        for(int i=0; i<n; i++)
            scanf("%s", s[0][i]);
        getchar();
        for(int i=0; i<n; i++)
            scanf("%s", s[1][i]);
        for(int i=0; i<n; i++)
            for(int j=0; j<m; j++)
            {
                if(s[0][i][j]=='#' && s[1][i][j]=='#')
                    s[0][i][j]=s[1][i][j]='*';
                else if(s[0][i][j]=='#' && s[1][i][j]=='*')
                    s[0][i][j]=s[1][i][j]='*';
                else if(s[0][i][j]=='*' && s[1][i][j]=='#')
                    s[0][i][j]=s[1][i][j]='*';
            }

        if(bfs())puts("YES");
        else puts("NO");
    }
    return 0;
}
