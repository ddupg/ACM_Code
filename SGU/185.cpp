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

const int maxn=455;
const int maxm=80000+100;
const int oo=0x3f3f3f3f;

struct Edge
{
    int v, c, nxt;
} ;

int n, m, tot, head[maxn], d[maxn], vis[maxn];
Edge edge[maxm<<1];

void add(int u, int v, int w)
{
    edge[tot].v=v;
    edge[tot].c=w;
    edge[tot].nxt=head[u];
    head[u]=tot++;
}

struct qnode
{
    int u, d;
    qnode(int u, int d):u(u),d(d){}
    bool operator < (const qnode& a)const
    {
        return d>a.d;
    }
};
priority_queue<qnode> q;

void Dijkstra(int s)
{
    clr(d, 0x3f);
    clr(vis, 0);
    q.push(qnode(s, 0));
    d[s]=0;
    while(!q.empty())
    {
        qnode x=q.top();
        q.pop();
        if(vis[x.u])continue ;
        vis[x.u]=true;
        for(int i=head[x.u]; ~i; i=edge[i].nxt)
        {
            int v=edge[i].v, w=edge[i].c;
            if(d[v]>d[x.u]+w)
            {
                d[v]=d[x.u]+w;
                q.push(qnode(v, d[v]));
            }
        }
    }
}

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
        {
            flow+=dfs(SS, oo);
            if(flow>=2)return flow;
        }
        return flow;
    }

    bool solve(int u, int* ans, int& cnt)
    {
        if(u==TT)
        {
            ans[cnt++]=u;
            return true;
        }
        for(int& i=head[u]; ~i; i=e[i].nxt)
            if(!used[i] && (i&1^1) && e[i^1].c)
                if(solve(e[i].v, ans, cnt))
                {
                    ans[cnt++]=u;
                    used[i]=true;
                    return true;
                }
        return false;
    }
} net;

int main()
{
    scanf("%d%d", &n, &m);
    clr(head, 0xff);
    while(m--)
    {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        add(u, v, w);
        add(v, u, w);
    }
    Dijkstra(1);
    net.init(1, n);
    for(int i=1; i<=n; i++)
        for(int j=head[i]; ~j; j=edge[j].nxt)
        {
            int v=edge[j].v, w=edge[j].c;
            if(d[i]+w==d[v])
            {
                net.add(i, v, 1);
                net.add(v, i, 0);
            }
        }
    if(net.dinic()<2)
        puts("No solution");
    else
    {
        for(int i=0; i<2; i++)
        {
            int ans[maxn], cnt=0;
            net.solve(1, ans, cnt);
            for(int i=cnt-1; i>=0; i--)
            {
                if(i!=cnt-1)putchar(' ');
                printf("%d", ans[i]);
            }
            puts("");
        }
    }
    return 0;
}
