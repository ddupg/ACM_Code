#include <iostream>
#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;
const int maxn=30000+10;
const int oo = 0x3f3f3f3f;

int readint()
{
    char c=getchar();
    while(!isdigit(c))c=getchar();
    int x=0;
    while(isdigit(c))
    {
        x=x*10+c-'0';
        c=getchar();
    }
    return x;
}

struct Edge
{
    int u, v, d;
    Edge(int u=0, int v=0, int d=0):u(u), v(v), d(d){}
};
struct qnode
{
    int u, d;
    qnode(int u, int d):u(u), d(d){}
    bool operator < (const qnode a)const
    {
        return d>a.d;
    }
};

int n, m, d[maxn];
Edge edge[5*maxn];
int tail[maxn], next[5*maxn], tot;
bool vis[maxn];

void init()
{
    memset(d, 0x3f, sizeof d);
    memset(vis, 0, sizeof vis);
    memset(tail, -1, sizeof tail);
    tot=0;
}

void AddEdge(int u, int v, int dis)
{
    edge[++tot]=Edge(u, v, dis);
    next[tot]=tail[u];
    tail[u]=tot;
}

int Dijkstra()
{
    priority_queue<qnode> q;
    q.push(qnode(1, 0));
    d[1]=0;
    while(!q.empty())
    {
        qnode x=q.top();
        q.pop();
        if(vis[x.u])continue ;
        vis[x.u]=true;
        if(x.u==n)return d[n];
        for(int i=tail[x.u]; ~i; i=next[i])
        {
            Edge& e=edge[i];
            if(d[e.v]>d[e.u]+e.d)
            {
                d[e.v]=d[e.u]+e.d;
                q.push(qnode(e.v, d[e.v]));
            }
        }
    }
    return d[n];
}

int main()
{
    while(~scanf("%d%d", &n, &m))
    {
        init();
        while(m--)
        {
            int u=readint(), v=readint(), dis=readint();
            AddEdge(u, v, dis);
        }
        printf("%d\n", Dijkstra());
    }
    return 0;
}
