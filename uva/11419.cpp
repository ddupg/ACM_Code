#include <iostream>
#include <cstdio>
#include <cstring>
#define mem(a, val) memset((a), (val), sizeof a)
using namespace std;
const int maxn=1100;
const int maxm=1000000+10;

struct Edge
{
    int to, next;
} edge[maxm];
bool usedx[maxn], usedy[maxn];
int R, C, n, tot, linkx[maxn], linky[maxn], head[maxn];

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
    usedx[u]=true;
    for(int i=head[u]; ~i; i=edge[i].next)
    {
        int v=edge[i].to;
        if(usedy[v])continue ;
        usedy[v]=true;
        if(linky[v]==-1 || match(linky[v]))
        {
            linky[v]=u;
            linkx[u]=v;
            return true;
        }
    }
    return false;
}

int hungary()
{
    mem(linkx, -1);
    mem(linky, -1);
    int ans=0;
    for(int i=1; i<=R; i++)
    {
        mem(usedy, 0);
        ans+=match(i);
    }
    return ans;
}

void input()
{
    init();
    while(n--)
    {
        int u, v;
        scanf("%d%d", &u, &v);
        AddEdge(u, v);
    }
}

void solve()
{
    printf("%d", hungary());
    mem(usedx, 0);
    mem(usedy, 0);
    for(int i=1; i<=R; i++)
        if(-1==linkx[i])
            match(i);
    for(int i=1; i<=R; i++)
        if(!usedx[i])
            printf(" r%d", i);
    for(int i=1; i<=C; i++)
        if(usedy[i])
            printf(" c%d", i);
    puts("");
}

int main()
{
    while(~scanf("%d%d%d", &R, &C, &n) && R+C+n)
    {
        input();
        solve();
    }
    return 0;
}
