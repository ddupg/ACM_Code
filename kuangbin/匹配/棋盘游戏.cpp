#include <iostream>
#include <cstdio>
#include <cstring>
#define mem(a, val) memset(a, val, sizeof a)
using namespace std;
const int maxn=110;

int n, m, k, link[maxn], tot, head[maxn];
bool used[maxn];

struct Edge
{
    int to, next;
    bool flag;
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
    edge[tot].flag=true;
    head[u]=tot++;
}

bool match(int u)
{
    for(int i=head[u]; ~i; i=edge[i].next)if(edge[i].flag)
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
    for(int i=1; i<=n; i++)
    {
        mem(used, 0);
        ans+=match(i);
    }
    return ans;
}


int main()
{
    int kase=0;
    while(~scanf("%d%d%d", &n, &m, &k))
    {
        init();
        while(k--)
        {
            int u, v;
            scanf("%d%d", &u, &v);
            AddEdge(u, v);
        }
        int cnt=hungary(), ans=0;
        for(int i=0; i<tot; i++)
        {
            edge[i].flag=false;
            if(cnt>hungary())
                ans++;
            edge[i].flag=true;
        }
        printf("Board %d have %d important blanks for %d chessmen.\n", ++kase, ans, cnt);
    }
    return 0;
}
