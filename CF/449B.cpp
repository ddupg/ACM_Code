#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>
#include <queue>
#define clr(a, x) memset(a, x, sizeof a)
using namespace std;
typedef long long LL;
const int maxn=100000+100;

struct Edge
{
    int v, w, flag;
    Edge(int v, int w, int flag):v(v), w(w), flag(flag){}
};
struct Node
{
    int v;
    LL w;
    Node(int v, LL w):v(v), w(w){}
    bool operator < (const Node a)const
    {
        return w>a.w;
    }
};

struct Dijkstra
{
    int n, pre[maxn];
    LL d[maxn];
    bool vis[maxn];
    vector<Edge> edge;
    vector<int> G[maxn];
    priority_queue<Node> q;
    void init(int n)
    {
        this->n=n;
        for(int i=0; i<=n; i++)
            G[i].clear();
        edge.clear();
    }
    void add(int u, int v, int w, int flag)
    {
        G[u].push_back(edge.size());
        edge.push_back(Edge(v, w, flag));
    }
    int solve(int S)
    {
        clr(d, 0x3f);
        clr(vis, 0);
        clr(pre, -1);
        d[S]=0;
        q.push(Node(S, 0));
        while(!q.empty())
        {
            Node x=q.top();
            q.pop();
            if(vis[x.v])continue ;
            vis[x.v]=true;
            for(int i=0; i<G[x.v].size(); i++)
            {
                Edge& e=edge[G[x.v][i]];
                if(d[e.v]>d[x.v]+e.w)
                {
                    d[e.v]=d[x.v]+e.w;
                    pre[e.v]=e.flag;
                    q.push(Node(e.v, d[e.v]));
                }
                else if(d[e.v]==d[x.v]+e.w && pre[e.v]==1 && e.flag==0)
                    pre[e.v]=0;
            }
        }
        int ans=0;
        for(int i=2; i<=n; i++)
            if(pre[i]==1)
                ans++;
        return ans;
    }
} g;

int main()
{
    int n, m, k;
    scanf("%d%d%d", &n, &m, &k);
    g.init(n);
    while(m--)
    {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        g.add(u, v, w, 0);
        g.add(v, u, w, 0);
    }
    for(int i=0; i<k; i++)
    {
        int v, w;
        scanf("%d%d", &v, &w);
        g.add(1, v, w, 1);
        g.add(v, 1, w, 1);
    }
    printf("%d\n", k-g.solve(1));
    return 0;
}
