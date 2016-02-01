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
#define rep(i,n) for(int i=0;i<(int)n;i++)
#define rep1(i,x,y) for(int i=x;i<=(int)y;i++)
using namespace std;
typedef long long LL;
typedef pair<int, int> pii;
typedef pair<int, pii> piii;

const int maxn=220;
const int maxm=maxn*maxn;
const int oo=0x3f3f3f3f;

int n, m, L;

struct Edge
{
    int v, c, nxt;
} ;

struct Dinic
{
    Edge e[maxm<<1];
    int SS, TT, idx, head[maxn];
    int dis[maxn], cur[maxn];
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

        e[idx].v = u, e[idx].c = c;
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

piii e[maxm];

int main()
{
    int n, m;
    while(~scanf("%d", &n) && n)
    {
        int sum=0, s=0, t=n+1;
        net.init(s, t);
        for(int i=1; i<=n; i++)
        {
            int x;
            scanf("%d", &x);
            sum+=x;
            if(x)net.add(s, i, x);
        }
        for(int i=1; i<=n; i++)
        {
            int x;
            scanf("%d", &x);
            if(x)net.add(i, t, x);
        }
        scanf("%d", &m);
        for(int i=0; i<m; i++)
            scanf("%d%d%d", &e[i].snd.fst, &e[i].snd.snd, &e[i].fst);
        sort(e, e+m);
        if(sum==0)
        {
            puts("0");
            continue ;
        }
        int flow=0, ans=-1;
        for(int i=0; i<m; i++)
        {
            int u=e[i].snd.fst, v=e[i].snd.snd, w=e[i].fst;
            net.add(u, v, oo);
            flow+=net.dinic();
            if(flow==sum)
            {
                ans=w;
                break;
            }
        }
        if(~ans)printf("%d\n", ans);
        else puts("No Solution");
    }
    return 0;
}
