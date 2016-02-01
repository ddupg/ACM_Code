#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;
typedef long long LL;

const int maxn=3200;
const int oo=0x3f3f3f3f;

struct Edge
{
    int u, v, cap, flow;
    Edge(int u, int v, int c, int f):u(u), v(v), cap(c), flow(f){}
};
struct Dinic
{
    int n, m, s, t;
    vector<Edge> edge;
    vector<int> G[maxn];
    bool vis[maxn];
    int d[maxn], cur[maxn];
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
    int MaxFlow(int s, int t)
    {
        this->s=s;
        this->t=t;
        int flow=0;
        while(bfs())
        {
            memset(cur, 0, sizeof cur);
            flow+=dfs(s, oo);
        }
        return flow;
    }
} net;

int a[110];
int tot=0;
vector<pair<int, int> > divi[maxn];

void split(int x, vector<pair<int, int> >& v)
{
    for(int i=2; x/i>=i; i++)
        while(x%i==0)
        {
            v.push_back(make_pair(i, ++tot));
            x/=i;
        }
    if(x>1)
        v.push_back(make_pair(x, ++tot));
}

int main()
{
    int n, m;
    scanf("%d%d", &n, &m);
    for(int i=1; i<=n; i++)
    {
        scanf("%d", a+i);
        split(a[i], divi[i]);
    }
    net.init(tot+10);
    int S=0, T=tot+1;
    for(int i=1; i<=n; i++)
    {
        if(i&1)
        {
            for(int j=0; j<divi[i].size(); j++)
                net.AddEdge(S, divi[i][j].second, 1);
        }
        else
        {
            for(int j=0; j<divi[i].size(); j++)
                net.AddEdge(divi[i][j].second, T, 1);
        }
    }
    while(m--)
    {
        int u, v;
        scanf("%d%d", &u, &v);
        if(v&1)swap(u, v);
        for(int i=0; i<divi[u].size(); i++)
            for(int j=0; j<divi[v].size(); j++)
                if(divi[u][i].first==divi[v][j].first)
                    net.AddEdge(divi[u][i].second, divi[v][j].second, 1);
    }
    printf("%d\n", net.MaxFlow(S, T));
    return 0;
}
