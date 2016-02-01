#include <iostream>
#include <cstdio>
#include <cstring>
#define mem(a, val) memset(a, val, sizeof a)
using namespace std;
const int maxn=3630;

int n, m, link[maxn], tot, head[maxn];
bool used[maxn];

int white, black;
char g[610][610];
int id[610][610];
bool clr[610][610];
int dx[]= {0, 0, 1, -1};
int dy[]= {1, -1, 0, 0};

struct Edge
{
    int to, next;
} edge[maxn*100];

void init()
{
    tot=0;
    mem(head, -1);
}

void AddEdge(int u, int v)
{
    edge[tot].to=v;
    edge[tot].next=head[u];
    head[u]=tot++;
}

bool match(int u)
{
    for(int i=head[u]; ~i; i=edge[i].next)
    {
        int v=edge[i].to;
        if(used[v])continue ;
        used[v]=true;
        if(link[v]==-1 || match(link[v]))
        {
            link[v]=u;
            return true;
        }
    }
    return false;
}

int hungary()
{
    int ans=0;
    mem(link, -1);
    for(int i=1; i<=white; i++)
    {
        mem(used, 0);
        ans+=match(i);
    }
    return ans;
}

bool inside(int x, int y)
{
    return x<=m && x>=1 && y<=m && y>=1;
}

int main()
{
    int T, kase=0;
    scanf("%d", &T);
    while(T--)
    {
        init();
        scanf("%d", &m);
        white=0, black=0;
        for(int i=1; i<=m; i++)
        {
            scanf("%s", g[i]+1);
            for(int j=1; j<=m; j++)
                if(g[i][j]=='#')
                {
                    clr[i][j]=(i+j)&1;
                    if(clr[i][j])id[i][j]=++black;
                    else id[i][j]=++white;
                }
        }

        for(int i=1; i<=m; i++)
        {
            for(int j=1; j<=m; j++)if(!clr[i][j] && g[i][j]=='#')
                {
                    for(int k=0; k<4; k++)
                    {
                        int x=i+dx[k], y=j+dy[k];
                        if(inside(x, y) && g[x][y]=='#')
                            AddEdge(id[i][j], id[x][y]);
                    }
                }
        }
        printf("Case %d: %d\n", ++kase, hungary());
    }
    return 0;
}
