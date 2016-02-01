#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>
#include <algorithm>
#define mp make_pair
#define pb push_back
#define all(a) a.begin(), a.end()
using namespace std;
typedef pair<int, int> pii;
const int maxn=1100;
const int oo = 2e10+10;

struct Edge
{
    int u, v, cap, flow;
    Edge(int u, int v, int c, int f):u(u), v(v), cap(c), flow(f){}
};

int n, m, C;
vector<pii> ans;
int cutedge[10000], cnt;

struct Dinic
{
    int n, m, s, t;
    vector<Edge> edge;
    vector<int> G[maxn];
    bool vis[maxn];
    int d[maxn];
    int cur[maxn];

    void init(int n)
    {
        this->n=n;
        for(int i=0; i<=n; i++)
            G[i].clear();
        edge.clear();
    }

    void AddEdge(int u, int v, int cap)
    {
        edge.push_back(Edge(u, v, cap, 0));
        edge.push_back(Edge(v, u, 0, 0));
        m=edge.size();
        G[u].push_back(m-2);
        G[v].push_back(m-1);
    }

    bool bfs()
    {
        memset(vis, 0, sizeof vis);
        queue<int> q;
        q.push(s);
        d[s]=0;
        vis[s]=1;
        while(!q.empty())
        {
            int x=q.front();
            q.pop();
            for(int i=0; i<G[x].size(); i++)
            {
                Edge& e=edge[G[x][i]];
                if(!vis[e.v] && e.cap>e.flow)
                {
                    vis[e.v]=true;
                    d[e.v]=d[x]+1;
                    q.push(e.v);
                }
            }
        }
        return vis[t];
    }

    int dfs(int x, int a)
    {
        if(x==t || a==0)return a;
        int flow=0, f;
        for(int& i=cur[x]; i<G[x].size(); i++)
        {
            Edge& e=edge[G[x][i]];
            if(d[x]+1==d[e.v] && (f=dfs(e.v, min(a, e.cap-e.flow)))>0)
            {
                e.flow+=f;
                edge[G[x][i]^1].flow-=f;
                flow+=f;
                a-=f;
                if(a==0)break;
            }
        }
        return flow;
    }

    bool Maxflow(int s, int t)
    {
        this->s=s;
        this->t=t;
        int flow=0;
        while(bfs())
        {
            memset(cur, 0, sizeof cur);
            flow+=dfs(s, oo);
            if(flow>=C)return true;
        }
        return flow>=C;
    }
} net;

bool change(int x)
{
    for(int i=0; i<net.m; i++)
        net.edge[i].flow=0;
    int tmp=net.edge[x].cap;
    net.edge[x].cap=C;
    bool ans=net.Maxflow(1,n);
    for(int i=0; i<net.m; i++)
        net.edge[i].flow=0;
    net.edge[x].cap=tmp;
    return ans;
}

int main()
{
    int kase=0;
    while(~scanf("%d%d%d", &n, &m, &C) && n)
    {
        net.init(n);
        while(m--)
        {
            int u, v, c;
            scanf("%d%d%d", &u, &v, &c);
            net.AddEdge(u, v, c);
        }
        printf("Case %d: ", ++kase);
        if(net.Maxflow(1, n))
            puts("possible");
        else
        {
            cnt=0;
            ans.clear();
            for(int i=0; i<net.m; i++)
                if(net.edge[i].flow==net.edge[i].cap && net.edge[i].flow>0)
                    cutedge[cnt++]=i;

            for(int i=0; i<cnt; i++)
                if(change(cutedge[i]))
                    ans.pb(mp(net.edge[cutedge[i]].u, net.edge[cutedge[i]].v));
            if(!ans.size())
                puts("not possible");
            else
            {
                printf("possible option:");
                sort(all(ans));
                for(int i=0; i<ans.size(); i++)
                {
                    if(i)putchar(',');
                    printf("(%d,%d)", ans[i].first, ans[i].second);
                }
                puts("");
            }
        }
    }
    return 0;
}
