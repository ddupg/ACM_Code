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

const int maxn=600;
const int maxm=maxn*maxn;
const int oo=0x3f3f3f3f;

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
        clr(head, 0xff);
    }

    void add(int u, int v, int c)
    {
        e[idx].v = v, e[idx].c = c;
        e[idx].nxt = head[u];
        head[u] = idx++;

        e[idx].v=u, e[idx].c=0;
        e[idx].nxt=head[v];
        head[v]=idx++;
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
} net;

int candy[15][30], id[15][30];

int main()
{
    int T, kase=0;
    scanf("%d", &T);
    while(T--)
    {
        int n, m, idx=0, ans=0;
        scanf("%d%d", &n, &m);
        clr(candy, 0);
        clr(id, 0);
        int SS=0, TT=n+m+10;
        net.init(SS, TT);
        for(int i=1; i<=n; i++)
        {
            int k, x;
            scanf("%d", &k);
            while(k--)
            {
                scanf("%d", &x);
                candy[i][x]++;
            }
        }
        for(int i=1; i<=m; i++)
        {
            if(candy[1][i])
                net.add(SS, n+i, candy[1][i]);
            net.add(n+i, TT, 1);
        }
        for(int i=2; i<=n; i++)
            for(int j=1; j<=m; j++)
            {
                if(!candy[i][j])
                    net.add(n+j, i, 1);
                else if(candy[i][j]>1)
                    net.add(i, n+j, candy[i][j]-1);
            }
        printf("Case #%d: %d\n", ++kase, net.dinic());
    }
    return 0;
}

/**
2
2 5
6 1 1 1 1 1 1
3 1 2 2
3 5
4 1 2 1 1
3 2 2 2
5 1 3 4 4 3
**/
