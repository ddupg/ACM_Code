#include <iostream>
#include <cstdio>
#include <algorithm>
#include <queue>
#include <cstring>
#include <vector>
using namespace std;
const int maxn=1100;
const double oo = 1e9;

struct Edge
{
    int u, v;
    double t, d;
    Edge(int u, int v, double t, double d):u(u), v(v), t(t), d(d){}
};
struct qnode
{
    int u;
    double d;
    qnode(int u, double d):u(u), d(d){}
    bool operator < (const qnode& a)const
    {
        return d>a.d;
    }
};

vector<Edge> edge;
vector<int> G[maxn];
int n, m, S, T, pre[maxn];
double d[maxn];
bool vis[maxn];

void init()
{
    for(int i=0; i<=n; i++)G[i].clear();
    edge.clear();
}

void AddEdge(int u, int v, double t, double dis)
{
    G[u].push_back(edge.size());
    edge.push_back(Edge(u, v, t, dis));
}

bool Dijkstra(double cur)
{
    memset(vis, 0, sizeof vis);
    memset(pre, -1, sizeof pre);
    for(int i=1; i<=n; i++)d[i]=oo;
    d[S]=0;
    priority_queue<qnode> q;
    q.push(qnode(S, 0));
    while(!q.empty())
    {
        qnode x=q.top();
        q.pop();
        if(vis[x.u])continue ;
        vis[x.u]=true;
        if(x.u==T)return true;
        for(int i=0; i<G[x.u].size(); i++)
        {
            Edge& e=edge[G[x.u][i]];
            if(e.t<=cur && d[e.v]>d[x.u]+e.d)
            {
                d[e.v]=d[e.u]+e.d;
                pre[e.v]=x.u;
                q.push(qnode(e.v, d[e.v]));
            }
        }
    }
    return d[T]<oo;
}

void printRoad(int x)
{
    if(x==S)
    {
        printf("%d", x);
        return ;
    }
    printRoad(pre[x]);
    printf(" %d", x);
}

int main()
{
    while(~scanf("%d%d", &n, &m))
    {
        init();
        scanf("%d%d", &S, &T);
        vector<double> tem;
        while(m--)
        {
            int u, v;
            double t, d;
            scanf("%d%d%lf%lf", &u, &v, &t, &d);
            AddEdge(u, v, t, d);
            AddEdge(v, u, t, d);
            tem.push_back(t);
        }
        sort(tem.begin(), tem.end());
        int L=0, R=unique(tem.begin(), tem.end())-tem.begin()-1;
        while(L<R)
        {
            int mid=(L+R)>>1;
            if(Dijkstra(tem[mid]))
                R=mid;
            else L=mid+1;
        }
        Dijkstra(tem[R]);
        printRoad(T);
        printf("\n%.1lf %.1lf\n", d[T], tem[R]);
    }
    return 0;
}
