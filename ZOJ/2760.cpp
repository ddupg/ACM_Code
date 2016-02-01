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
#define ls (rt<<1)
#define rs (ls|1)
#define lson l, mid, ls
#define rson mid+1, r, rs
using namespace std;
typedef long long LL;
typedef pair<int, int> pii;

const int maxn=110;
const int maxm=maxn*maxn;
const int oo=0x3f3f3f3f;

struct Edge
{
    int v, nxt, c;
};

struct Dinic
{
    Edge e[maxm<<1];
    int SS, TT, idx, head[maxn];
    int dis[maxn], cur[maxn];
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
        for (int& i = cur[u]; ~i; i = e[i].nxt)
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
        {
            memcpy(cur, head, sizeof cur);
            flow+=dfs(SS, oo);
        }
        return flow;
    }
} net;

int g[maxn][maxn], d[maxn][maxn], f[maxn][maxn];

int main()
{
    int n;
    while(~scanf("%d", &n))
    {
        for(int i=0; i<n; i++)
            for(int j=0; j<n; j++)
            {
                scanf("%d", &g[i][j]);
                if(g[i][j]==-1)d[i][j]=oo;
                else d[i][j]=g[i][j];
                if(i==j)d[i][j]=0;
            }
        for(int k=0; k<n; k++)
            for(int i=0; i<n; i++)
                for(int j=0; j<n; j++)
                    d[i][j]=min(d[i][j], d[i][k]+d[k][j]);
        int SS, TT;
        scanf("%d%d", &SS, &TT);
        if(SS==TT)
        {
            puts("inf");
            continue ;
        }
        net.init(SS, TT);
        clr(f, 0);
        for(int i=0; i<n; i++)if(d[SS][i]<oo)
            for(int j=0; j<n; j++)if(g[i][j]>=0)
                if(d[SS][i]+g[i][j]==d[SS][j])
                    net.add(i, j, 1);
        printf("%d\n", net.dinic());
    }
    return 0;
}
