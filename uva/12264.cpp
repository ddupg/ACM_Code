#include <iostream>
#include <cstdio>
#include <cstring>
#include <queue>
#define clr(a, x) memset(a, x, sizeof a)
#define pb push_back
using namespace std;

const int maxn=210;
const int maxm=20000+100;
const int oo=0x3f3f3f3f;

struct Edge
{
    int v, c, nxt;
} ;

struct Dinic
{
    Edge e[maxm<<1];
    int SS, TT, idx, head[maxn];
    int dis[maxn];
    bool vis[maxn];
    bool used[maxm];
    queue<int>q;

    void init(int s, int t)
    {
        SS=s, TT=t;
        idx = 0;
        clr(head, 0xff);
    }

    void add(int u, int v, int c)
    {
        e[idx].v = v, e[idx].c = c;
        e[idx].nxt = head[u];
        head[u] = idx++;

        e[idx].v = u, e[idx].c = 0;
        e[idx].nxt = head[v];
        head[v] = idx++;
    }

    bool bfs()
    {
        clr(dis, 0xff);
        clr(vis, 0);
        dis[SS] = 0, vis[SS] = 1;
        q.push(SS);
        while (!q.empty())
        {
            int u = q.front();
            q.pop();
            vis[u] = 0;
            for (int i = head[u]; ~i; i = e[i].nxt)
            {
                int v = e[i].v, c = e[i].c;
                if (dis[v] == -1 && c)
                {
                    dis[v] = dis[u] + 1;
                    if (!vis[v])
                    {
                        vis[v] = 1;
                        q.push(v);
                    }
                }
            }
        }
        return dis[TT] != -1;
    }

    int dfs(int u, int flow)
    {
        if (u == TT) return flow;
        int tf = 0, f;
        for (int i = head[u]; ~i; i = e[i].nxt)
        {
            int v = e[i].v, c = e[i].c;
            if (dis[u]+1 == dis[v] && c && (f = dfs(v, min(flow-tf, c))))
            {
                e[i].c -= f, e[i^1].c += f;
                tf += f;
                if (tf == flow) return tf;
            }
        }
        if (!tf) dis[u] = -1;
        return tf;
    }

    int dinic()
    {
        int flow=0;
        while (bfs())
            flow+=dfs(SS, oo);
        return flow;
    }
} net;

int n, arm[maxn];
char g[maxn][maxn];

bool judge(int lim)
{
    int S=0, T=n*2+1, sum=0;
    net.init(S, T);
    for(int i=1; i<=n; i++) if(arm[i])
        {
            bool f=0;
            net.add(S, i, arm[i]);
            net.add(i, i+n, oo);
            for(int j=1; j<=n; j++)
                if(g[i][j]=='Y')
                {
                    if(!arm[j]) f=true;
                    else net.add(i, j+n, oo);
                }
            if(f) net.add(i+n, T, lim), sum+=lim;
            else net.add(i+n, T, 1), ++sum;
        }
    return net.dinic()==sum;
}

int main()
{
    int T;
    scanf("%d", &T);
    while(T-- && ~scanf("%d", &n))
    {
        for(int i=1; i<=n; i++)
            scanf("%d", arm+i);
        for(int i=1; i<=n; i++)
            scanf("%s", g[i]+1);

        int L=0, R=oo;
        while(L<R)
        {
            int mid=L+R+1>>1;
            if(judge(mid))L=mid;
            else R=mid-1;
        }
        printf("%d\n", L);
    }
    return 0;
}
