#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#define mem(a, val) memset(a, val, sizeof a)
using namespace std;
const int maxn=1010;
const int maxm=250000+100;

struct Node
{
    int tm, sx, sy, tx, ty;
} node[maxn];

struct Edge
{
    int to, next;
} edge[maxm];
int n, tot, head[maxn], link[maxn];
bool used[maxn];

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
        if(!used[v])
        {
            used[v]=true;
            if(link[v]==-1 || match(link[v]))
            {
                link[v]=u;
                return true;
            }
        }
    }
    return false;
}

int hungary()
{
    mem(link, -1);
    int ans=0;
    for(int i=1; i<=n; i++)
    {
        mem(used, 0);
        ans+=match(i);
    }
    return ans;
}

int dist(int x1, int y1, int x2, int y2)
{
    return abs(x1-x2)+abs(y1-y2);
}

int main()
{
    int T;
    scanf("%d", &T);
    while(T--)
    {
        scanf("%d", &n);
        init();
        for(int i=1; i<=n; i++)
        {
            int a, b;
            scanf("%d:%d %d %d %d %d", &a, &b, &node[i].sx, &node[i].sy, &node[i].tx, &node[i].ty);
            node[i].tm=a*60+b;
        }
        for(int i=1; i<=n; i++)
            for(int j=1; j<=n; j++)if(i!=j)
            if(node[i].tm+dist(node[i].sx, node[i].sy, node[i].tx, node[i].ty)
               +dist(node[i].tx, node[i].ty, node[j].sx, node[j].sy)<node[j].tm)
                AddEdge(i, j+n);
        printf("%d\n", n-hungary());
    }
    return 0;
}
