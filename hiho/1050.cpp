#include <iostream>
#include <cstring>
#include <cstdio>
#include <algorithm>
#include <queue>
using namespace std;
const int maxn=100000+100;

struct Edge
{
    int v, nxt;
} edge[maxn<<1];

int n, tot, head[maxn], d[maxn];
bool vis[maxn];

void init()
{
    memset(head, -1, sizeof head);
    tot=0;
}
void AddEdge(int u, int v)
{
    edge[tot].v=v;
    edge[tot].nxt=head[u];
    head[u]=tot++;
}
int bfs(int s)
{
    queue<int> q;
    int t=s;
    memset(vis, 0, sizeof vis);
    q.push(s);
    d[s]=0;
    vis[s]=1;
    while(!q.empty())
    {
        int u=q.front();
        q.pop();
        t=u;
        for(int i=head[u]; ~i; i=edge[i].nxt)
        {
            int v=edge[i].v;
            if(vis[v])continue ;
            d[v]=d[u]+1;
            vis[v]=1;
            q.push(v);
        }
    }
    return t;
}

int main()
{
    while(~scanf("%d", &n))
    {
        init();
        for(int i=0; i<n-1; i++)
        {
            int u, v;
            scanf("%d%d", &u, &v);
            AddEdge(u, v);
            AddEdge(v, u);
        }
        int rt=bfs(1);
        rt=bfs(rt);
        printf("%d\n", d[rt]);
    }
    return 0;
}
