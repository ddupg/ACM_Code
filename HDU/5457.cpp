#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <queue>
#define clr(a, x) memset(a, x, sizeof a)
using namespace std;

const int maxn=1303;
const int maxm=maxn<<2;
const int oo=0x3f3f3f3f;

struct Edge
{
    int v, c, nxt;
};

struct Dinic
{
    Edge e[maxn<<1];
    int S, T, idx, H[maxn];
    int d[maxn];
    bool vis[maxn];
    queue<int> q;

    void init(int s, int t)
    {
        S=s, T=t;
        idx=0;
        clr(H, -1);
    }

    void add(int u, int v, int c)
    {
        e[idx].v=v, e[idx].c=c;
        e[idx].nxt=H[u];
        H[u]=idx++;

        e[idx].v=u, e[idx].c=0;
        e[idx].nxt=H[v];
        H[v]=idx++;
    }
    bool bfs()
    {
        clr(d, 0xff);
        clr(vis, 0);
        d[S]=0, vis[S]=1;
        q.push(S);
        while(!q.empty())
        {
            int u=q.front();
            q.pop();
            vis[u]=0;
            for(int i=H[u]; ~i; i=e[i].nxt)
            {
                int v=e[i].v, c=e[i].c;
                if(d[v]==-1 && c)
                {
                    d[v]=d[u]+1;
                    if(!vis[v])
                    {
                        vis[v]=1;
                        q.push(v);
                    }
                }
            }
        }
        return d[T]!=-1;
    }
    int dfs(int u, int flow)
    {
        if(u==T)return flow;
        int tf=0, f;
        for(int i=H[u]; ~i; i=e[i].nxt)
        {
            int v=e[i].v, c=e[i].c;
            if(d[u]+1==d[v] && c && (f=dfs(v, min(flow-tf, c))))
            {
                e[i].c-=f, e[i^1].c+=f;
                tf+=f;
                if(tf==flow)return tf;
            }
        }
        if(!tf)d[u]=-1;
        return tf;
    }
    int dinic()
    {
        int flow=0;
        while(bfs())
        {
            flow+=dfs(S, oo);
            if(flow>=oo)return oo;
        }
        return flow;
    }
} net;

int ch[maxn][2], cost[maxn][2], sz;

void dfs(int u, int f)
{
    for(int i=0; i<2; i++)if(~ch[u][i])
    {
        if(f==1)net.add(u, ch[u][i], cost[u][i]);
        else net.add(ch[u][i], u, cost[u][i]);
        dfs(ch[u][i], f);
    }
}

int main()
{
    int T, kase=0;
    scanf("%d", &T);
    while(T--)
    {
        int n, m;
        sz=0;
        clr(ch, 0xff);
        clr(cost, 0x3f);
        scanf("%d%d", &n, &m);
        int s=sz++, t=sz++;
        net.init(s, t);
        for(int i=0; i<n; i++)
        {
            int x, u=s, v=t;
            scanf("%d", &x);
            for(int i=7; i>=0; i--)
            {
                int c=x>>i&1;
                if(ch[u][c]==-1)ch[u][c]=sz++;
                u=ch[u][c];
            }
            for(int i=0; i<8; i++)
            {
                int c=x>>i&1;
                if(ch[v][c]==-1)ch[v][c]=sz++;
                v=ch[v][c];
            }
            net.add(u, v, oo);
        }
        for(int i=0; i<m; i++)
        {
            char op[10], str[10];
            int w;
            scanf("%s%s%d", op, str, &w);
            int x;
            if(op[0]=='S')reverse(str, str+strlen(str)), x=t;
            else x=s;
            for(int i=0; str[i]; i++)
            {
                int c=str[i]-'0';
                if(x==-1)break ;
                if(!str[i+1])cost[x][c]=min(cost[x][c], w);
                x=ch[x][c];
            }
        }
        dfs(s, 1);
        dfs(t, -1);
        int ans=net.dinic();
        printf("Case #%d: %d\n", ++kase, ans<oo?ans:-1);
    }
    return 0;
}
