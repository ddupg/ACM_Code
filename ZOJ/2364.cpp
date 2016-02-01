#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <queue>
using namespace std;
typedef pair<int, int> pii;

const int maxn = 1505;
const int maxm = 300005;
const int oo = 0x3f3f3f3f;

int n, m, L;
int lv[maxn], rank[maxn], in[maxn], out[maxn];

struct Edge
{
    int v, c, nxt;
} ;

bool cmp(const int &a, const int &b)
{
    return lv[a] < lv[b];
}

struct Dinic
{
    Edge e[maxm<<1];
    int SS, TT, idx, head[maxn];
    int dis[maxn];
    bool vis[maxn];
    queue<int>q;

    void init(int s, int t)
    {
        SS=s, TT=t;
        idx = 0;
        memset(head, 0xff, sizeof (head));
    }

    void add(int u, int v, int c)
    {
        e[idx].v = v, e[idx].c = c;
        e[idx].nxt = head[u];
        head[u] = idx++;
    }
    void greedy()
    {
        memset(in, 0, sizeof (in));
        memset(out, 0, sizeof (out));
        sort(rank+1, rank+1+n, cmp);
        in[SS] = oo;
        for (int i = 1; i <= n; ++i)
        {
            int u = rank[i];
            for (int j = head[u]; ~j; j = e[j].nxt)
            {
                int v = e[j].v, c = e[j].c;
                if (!(j & 1) && in[u] > out[u])
                {
                    int f = min(c, in[u]-out[u]);
                    in[v] += f, out[u] += f;
                }
            }
        }
        memset(in, 0, sizeof (in));
        in[TT] = oo;
        for (int i = n; i >= 1; --i)
        {
            int v = rank[i];
            for (int j = head[v]; ~j; j = e[j].nxt)
            {
                int u = e[j].v, c = e[j^1].c;
                if (j & 1 && out[u] > in[u])
                {
                    int f = min(c, min(out[u]-in[u], in[v]));
                    in[u] += f, in[v] -= f;
                    e[j].c += f, e[j^1].c -= f;
                }
            }
        }
    }
    bool bfs()
    {
        memset(dis, -1, sizeof (dis));
        memset(vis, 0, sizeof (vis));
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

int main()
{
    int T;
    scanf("%d", &T);
    while (T-- && ~scanf("%d%d%d", &n, &m, &L))
    {
        int s, t;
        for (int i = 1; i <= n; ++i)
        {
            rank[i] = i;
            scanf("%d", lv+i);
            if (lv[i] == 1) s = i;
            else if (lv[i] == L) t = i;
        }
        int a, b, c;
        net.init(s, t);
        for (int i = 0; i < m; ++i)
        {
            scanf("%d%d%d", &a, &b, &c);
            net.add(a, b, c), net.add(b, a, 0);
        }
        net.greedy();
        net.dinic();
        for (int i = 0; i < m; ++i)
            printf("%d\n", net.e[i<<1|1].c);
    }
    return 0;
}
