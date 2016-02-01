#include <iostream>
#include <cstdio>
#include <cstring>
#define mem(a, val) memset(a, val, sizeof a)
using namespace std;
const int maxn=330;

int n, p, link[maxn], tot, head[maxn];
bool used[maxn];

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
    for(int i=1; i<=n; i++)
    {
        mem(used, 0);
        ans+=match(i);
    }
    return ans;
}


int main()
{
    int T;
    scanf("%d", &T);
    while(T--)
    {
        scanf("%d%d", &p, &n);
        init();
        for(int i=1; i<=p; i++)
        {
            int m, v;
            scanf("%d", &m);
            while(m--)
            {
                scanf("%d", &v);
                AddEdge(v, i);
            }
        }
        puts(hungary()==p?"YES":"NO");
    }
    return 0;
}
