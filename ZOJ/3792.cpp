#pragma comment(linker, "/STACK:1024000000,1024000000")
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <string>
#include <list>
#include <cstdlib>
#include <queue>
#include <stack>
#include <cmath>
#define ALL(a) a.begin(), a.end()
#define clr(a, x) memset(a, x, sizeof a)
#define fst first
#define snd second
#define pb push_back
#define mp make_pair
using namespace std;
typedef long long LL;
typedef pair<int, int> pii;

const int maxn = 60;
const int maxm = maxn*maxn;
const double oo = 0x3f3f3f3f;

struct Edge
{
    int v, nxt, c;
} ;

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
        return dis[TT]!=-1;
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
                if (tf==flow) return tf;
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

    void rebuild()
    {
        for(int i=0; i<idx; i+=2)
        {
            if(e[i].c==0)
            {
                e[i].c=1;
                e[i^1].c=oo;
            }
            else if(e[i^1].c==0)
            {
                e[i^1].c=1;
                e[i].c=oo;
            }
            else e[i].c=e[i^1].c=oo;
        }
    }
} net;

int main()
{
    int TT, n, m, S, T;
    scanf("%d", &TT);
    while(TT--)
    {
        scanf("%d%d%d%d", &n, &m, &S, &T);
        net.init(S, T);
        int sum=0;
        for(int i=0; i<m; i++)
        {
            int u, v, w;
            scanf("%d%d%d", &u, &v, &w);
            net.add(u, v, w);
            net.add(v, u, w);
            sum+=w;
        }
        int flow=net.dinic();
        if(!flow)
        {
            puts("Inf");
            continue ;
        }
        net.rebuild();
        printf("%.2f\n", 1.0*(sum-flow)/net.dinic());
    }
    return 0;
}
