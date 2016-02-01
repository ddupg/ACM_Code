#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>
using namespace std;
const int maxn=1100;
const int oo = 0x3f3f3f3f;

template <class T>
inline bool scan_d(T &ret)
{
    char c;
    int sgn;
    if(c=getchar(),c==EOF) return 0; //EOF
    while(c!=' -' &&(c<'0' ||c>'9' )) c=getchar();
    sgn=(c==' -' )?-1:1;
    ret=(c==' -' )?0:(c-'0' );
    while(c=getchar(),c>='0' &&c<='9' ) ret=ret*10+(c-'0' );
    ret*=sgn;
    return 1;
}

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

    int Maxflow(int s, int t)
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

int cap[1<<10];

int main()
{
    int n, m, s, x;
    while(~scanf("%d%d", &n, &m))
    {
        net.init((1<<m)+m+2);
        memset(cap, 0, sizeof cap);
        int S=0, T=(1<<m)+m+1, x;
        for(int i=0; i<n; i++)
        {
            s=0;
            for(int j=0; j<m; j++)
            {
                scan_d(x);
                if(x)s|=1<<j;
            }
            cap[s]++;
        }
        for(int i=0; i<m; i++)
        {
            scan_d(x);
            net.AddEdge((1<<m)+i, T, x);
        }
        for(int i=1; i<(1<<m); i++)
        {
            if(!cap[i])continue ;
            net.AddEdge(S, i, cap[i]);
            for(int j=0; j<m; j++)
                if(1<<j&i)
                    net.AddEdge(i, (1<<m)+j, cap[i]);
        }
        printf("%s\n", n==net.Maxflow(S, T)?"YES":"NO");
    }
    return 0;
}
