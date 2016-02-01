#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <queue>
#define mem(a, val) memset((a), (val), sizeof(a))
using namespace std;
const int maxn=300000;
int vis[maxn], S, T;

int bfs()
{
    mem(vis, -1);
    queue<int> q;
    q.push(S);
    vis[S]=0;
    while(!q.empty())
    {
        int x=q.front();
        q.pop();
        if(x==T)return vis[T];
        if(x-1>=0 && vis[x-1]==-1)
        {
            q.push(x-1);
            vis[x-1]=vis[x]+1;
        }
        if(x+1<maxn && vis[x+1]==-1)
        {
            q.push(x+1);
            vis[x+1]=vis[x]+1;
        }
        if(x*2<maxn && vis[x*2]==-1)
        {
            q.push(x*2);
            vis[x*2]=vis[x]+1;
        }
    }
}

int main()
{
    while(~scanf("%d%d", &S, &T))
        printf("%d\n", bfs());
    return 0;
}
