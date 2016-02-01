#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cstring>
using namespace std;

const int maxn=210;
int map[maxn][maxn],visit[maxn],match[maxn];
int n;
bool dfs(int v)
{
    int i;
    for(i=1; i<=n; i++)
        if(map[v][i]&&!visit[i])
        {
            visit[i]=1;
            if(match[i]==-1||dfs(match[i]))
            {
                match[i]=v;
                return true;
            }
        }
    return false;
}

int hungry()
{
    int i,ans=0;
    memset(match,-1,sizeof(match));
    for(i=1; i<=n; i++)
    {
        memset(visit,0,sizeof(visit));
        if(dfs(i)) ans++;
    }
    return ans;
}

struct Node
{
    int x, y;
} node[maxn];

int main()
{
    int T;
    scanf("%d", &T);
    while(T--)
    {
        scanf("%d", &n);
        memset(map, 0, sizeof(map));
        for(int i=1; i<=n; i++)
        {
            scanf("%d%d", &node[i].x, &node[i].y);
            node[i].x=node[i].x+1>>1;
            node[i].y=node[i].y+1>>1;
            if(node[i].x>node[i].y)
                swap(node[i].x, node[i].y);
        }
        for(int i=1; i<=n; i++)
            for(int j=1; j<=n; j++)if(i!=j)
                    if(node[i].y<node[j].x)
                        map[i][j]=1;
        printf("%d0\n", n-hungry());
    }
    return 0;
}
