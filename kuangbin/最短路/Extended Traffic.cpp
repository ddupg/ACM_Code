#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cstring>
#include <queue>
using namespace std;
const int maxn=220;
const int oo = 0x3f3f3f3f;

struct Edge
{
    int u, v, d;
    Edge(int u, int v, int d):u(u), v(v), d(d) {}
};
vector<Edge> edge;
vector<int> G[maxn];
int n, m, d[maxn], val[maxn];
bool incircle[maxn];

void init()
{
    for(int i=1; i<=n; i++)
        G[i].clear();
    edge.clear();
}

void AddEdge(int u, int v, int dis)
{
    G[u].push_back(edge.size());
    edge.push_back(Edge(u, v, dis*dis*dis));
}

void spfa()
{
    memset(d, 0x3f, sizeof d);
    memset(incircle, 0, sizeof incircle);
    bool vis[maxn]= {0, 1};
    int cnt[maxn]= {0};
    d[1]=0;
    cnt[1]++;
    queue<int> q;
    q.push(1);
    while(!q.empty())
    {
        int x=q.front();
        q.pop();
        vis[x]=false;
        if(cnt[x]>n)
        {
            incircle[x]=true;
            continue ;
        }
        for(int i=0; i<G[x].size(); i++)
        {
            Edge& e=edge[G[x][i]];
            if(d[e.v]>d[x]+e.d)
            {
                d[e.v]=d[x]+e.d;
                if(!vis[e.v])
                {
                    vis[e.v]=true;
                    cnt[e.v]++;
                    q.push(e.v);
                }
            }
        }
    }
}

int main()
{
    int T, kase=0;
    scanf("%d", &T);
    while(T--)
    {
        scanf("%d", &n);
        init();
        for(int i=1; i<=n; i++)
            scanf("%d", val+i);
        scanf("%d", &m);
        while(m--)
        {
            int u, v;
            scanf("%d%d", &u, &v);
            AddEdge(u, v, val[v]-val[u]);
        }
        spfa();
        printf("Case %d:\n", ++kase);
        scanf("%d", &m);
        while(m--)
        {
            int t;
            scanf("%d", &t);
            if(incircle[t] || d[t]<3 || d[t]==oo)
                puts("?");
            else printf("%d\n", d[t]);
        }
    }
    return 0;
}
