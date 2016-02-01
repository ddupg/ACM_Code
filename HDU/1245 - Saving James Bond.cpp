#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <queue>
#include <cmath>
#include <vector>
using namespace std;
const int maxn=110;
const double INF=1e9;
const double eps=1e-9;
struct Point
{
    double x, y;
} p[maxn];
struct Edge
{
    int u, v;
    double dis;
    Edge(int u, int v, double dis):u(u), v(v), dis(dis){}
};
struct qnode
{
    int u, cnt;
    double dis;
    qnode(int u, double dis, int cnt):u(u), dis(dis), cnt(cnt){}
    bool operator < (const qnode x)const
    {
        return dis>x.dis || (fabs(dis-x.dis)<eps && cnt>x.cnt);
    }
};
double L;
int n;
vector<int> G[maxn];
vector<Edge> edge;
double getdis(int i, int j)
{
    return sqrt(pow(p[i].x-p[j].x, 2)+pow(p[i].y-p[j].y, 2));
}
void init()
{
    for(int i=0; i<=n; i++)
        G[i].clear();
    edge.clear();
}

void AddEdge(int u, int v, double dis)
{
    edge.push_back(Edge(u, v, dis));
    G[u].push_back(edge.size()-1);
    edge.push_back(Edge(v, u, dis));
    G[v].push_back(edge.size()-1);
}

bool Dijkstra()
{
    priority_queue<qnode> q;
    double d[maxn];
    int cnt[maxn];
    int vis[maxn]={0};
    for(int i=0; i<=n; i++)
        d[i]=i==0?0:INF;
    for(int i=0; i<=n; i++)
        cnt[i]=i==0?0:1e9;
    q.push(qnode(0, 0, 0));
    while(!q.empty())
    {
        qnode x=q.top();
        q.pop();
        if(vis[x.u])continue ;
        vis[x.u]=1;
        for(int i=0; i<G[x.u].size(); i++)
        {
            Edge e=edge[G[x.u][i]];
            if(d[e.v]>d[e.u]+e.dis)
            {
                d[e.v]=d[e.u]+e.dis;
                cnt[e.v]=cnt[e.u]+1;
                q.push(qnode(e.v, d[e.v], cnt[e.v]));
            }
            else if(fabs(d[e.v]-d[e.u]-e.dis)<eps && cnt[e.v]>cnt[e.u]+1)
            {
                cnt[e.v]=cnt[e.u]+1;
                q.push(qnode(e.v, d[e.v], cnt[e.v]));
            }
        }
    }
    if(d[n]>=INF)return 0;
    printf("%.2lf %d\n", d[n], cnt[n]);
    return 1;
}

int main()
{
    double dis;
    while(~scanf("%d%lf", &n,&L))
    {
        n+=1;
        init();
        p[0].x=0, p[0].y=0;
        for(int i=1; i<n; i++)
        {
            scanf("%lf%lf", &p[i].x, &p[i].y);
            for(int j=0; j<i; j++)
            {
                dis=getdis(i, j);
                if(!j)
                    dis-=7.5;
                if(dis<=L)
                    AddEdge(i, j, dis);
            }
            if(min(50-fabs(p[i].x), 50-fabs(p[i].y))<=L)
                AddEdge(i, n, min(50-fabs(p[i].x), 50-fabs(p[i].y)));
        }
        if(!Dijkstra())
            puts("can't be saved");
    }
    return 0;
}
