#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <queue>
#define mem(a, val) memset((a), (val), sizeof(a))
using namespace std;
const int maxn=35;
char s[maxn][maxn][maxn];
int vis[maxn][maxn][maxn];
int d[6][3]= {{1, 0, 0}, {0, 1, 0}, {0, 0, 1}, {-1, 0, 0}, {0, -1, 0}, {0, 0, -1}};
int m, n, h;
struct Node
{
    int x, y, z;
    Node(int x=0, int y=0, int z=0):x(x), y(y), z(z) {}
    bool operator == (Node a)
    {
        return x==a.x && y==a.y && z==a.z;
    }
};
bool inside(int x, int y, int z)
{
    return x>=0 && x<m && y>=0 && y<n && z>=0 && z<h;
}

int bfs()
{
    Node S, T;
    for(int i=0; i<m; i++)
        for(int j=0; j<n; j++)
            for(int k=0; k<h; k++)
            {
                if(s[i][j][k]=='S')
                    S=Node(i, j, k);
                if(s[i][j][k]=='E')
                    T=Node(i, j, k);
            }
    queue<Node> q;
    q.push(S);
    mem(vis, -1);
    vis[S.x][S.y][S.z]=0;
    while(!q.empty())
    {
        Node node=q.front();
        if(node==T)
            return vis[node.x][node.y][node.z];
        q.pop();
        for(int i=0; i<6; i++)
        {
            int nx=node.x+d[i][0], ny=node.y+d[i][1], nz=node.z+d[i][2];
            if(inside(nx, ny, nz) && vis[nx][ny][nz]==-1 && s[nx][ny][nz]!='#')
            {
                vis[nx][ny][nz]=vis[node.x][node.y][node.z]+1;
                q.push(Node(nx, ny, nz));
            }
        }
    }
    return -1;
}

int main()
{
    while(~scanf("%d%d%d", &m, &n, &h) && n+m+h)
    {
        for(int i=0; i<m; i++)
        {
            getchar();
            for(int j=0; j<n; j++)
                scanf("%s", s[i][j]);
        }
        int ans=bfs();
        if(ans>=0)
            printf("Escaped in %d minute(s).\n", ans);
        else puts("Trapped!");
    }
    return 0;
}
