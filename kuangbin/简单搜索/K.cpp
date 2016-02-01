#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <queue>
#include <algorithm>
#define mem(a, val) memset((a), (val), sizeof(a))
using namespace std;
int dx[]={0, 0, 1, -1};
int dy[]={1, -1, 0, 0};
int g[10][10], vis[10][10];
bool inside(int x, int y)
{
    return x>=0 && x<5 && y>=0 && y<5;
}

struct Node
{
    int x, y;
    Node(int x, int y):x(x), y(y){}
};

void bfs()
{
    mem(vis, -1);
    queue<Node> q;
    q.push(Node(0, 0));
    vis[0][0]=0;
    while(!q.empty())
    {
        Node t=q.front();
        q.pop();
        for(int i=0; i<4; i++)
        {
            int nx=t.x+dx[i], ny=t.y+dy[i];
            if(inside(nx, ny) && vis[nx][ny]==-1 && !g[nx][ny])
            {
                vis[nx][ny]=vis[t.x][t.y]+1;
                q.push(Node(nx, ny));
            }
        }
    }
}

void print(int x, int y)
{
    if(!x && !y)
    {
        puts("(0, 0)");
        return ;
    }
    for(int i=0; i<4; i++)
    {
        int nx=x+dx[i], ny=y+dy[i];
        if(inside(nx, ny) && vis[nx][ny]==vis[x][y]-1)
        {
            print(nx, ny);
            printf("(%d, %d)\n", x, y);
            return ;
        }
    }
}

int main()
{
    for(int i=0; i<5; i++)
        for(int j=0; j<5; j++)
            scanf("%d", &g[i][j]);
    bfs();
    print(4, 4);
    return 0;
}
