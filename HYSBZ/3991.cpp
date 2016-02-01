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
#define ls (rt<<1)
#define rs (ls|1)
#define lson l, mid, ls
#define rson mid+1, r, rs
#define sqr(x) ((x)*(x))
using namespace std;
typedef long long LL;
typedef pair<int, int> pii;

const int maxn=100000+100;
const int DEG=20;

struct Edge
{
    int v, w, nxt;
} E[maxn<<1];

int n, head[maxn], tot, deg[maxn];
LL dis[maxn];
int fa[maxn][20], id[maxn], fid[maxn], dfn;
queue<int> q;
set<int> S;

void AddEdge(int u, int v, int w)
{
    E[tot].v=v, E[tot].w=w, E[tot].nxt=head[u];
    head[u]=tot++;
}

void init()
{
    clr(head, -1);
    tot=dfn=0;
    S.clear();
}

void dfs(int u, int f)
{
    id[u]=++dfn;
    fid[dfn]=u;
    for(int i=head[u]; ~i; i=E[i].nxt)
    {
        int v=E[i].v;
        if(v==f)continue ;
        dfs(v, u);
    }
}

void bfs(int rt)
{
    deg[rt]=0;
    dis[rt]=0;
    fa[rt][0]=rt;
    q.push(rt);
    while(!q.empty())
    {
        int u=q.front();
        q.pop();
        for(int i=1; i<DEG; i++)
            fa[u][i]=fa[fa[u][i-1]][i-1];
        for(int i=head[u]; ~i; i=E[i].nxt)
        {
            int v=E[i].v;
            if(v==fa[u][0])continue ;
            deg[v]=deg[u]+1;
            dis[v]=dis[u]+E[i].w;
            fa[v][0]=u;
            q.push(v);
        }
    }
}

int LCA(int u, int v)
{
    if(deg[u]>deg[v])swap(u, v);
    int hu=deg[u], hv=deg[v];
    int tu=u, tv=v;
    for(int det=hv-hu, i=0; det; det>>=1, i++)
        if(det&1)
            tv=fa[tv][i];
    if(tu==tv)return tu;
    for(int i=DEG-1; i>=0; i--)
    {
        if(fa[tu][i]==fa[tv][i])
            continue ;
        tu=fa[tu][i];
        tv=fa[tv][i];
    }
    return fa[tu][0];
}

LL get(int u)
{
    if(S.size()==0)return 0;
    if(S.size()==1)
    {
        int x=fid[*S.begin()];
        return dis[u]+dis[x]-2*dis[LCA(x, u)];
    }

    set<int>::iterator it=S.lower_bound(id[u]);
    set<int>::iterator be=S.begin(), en=S.end();
    en--;
    int x=u, y=u;
    if(it==S.begin())
        x=fid[*it], y=fid[*en];
    else if(it==S.end())
        x=fid[*be], y=fid[*en];
    else y=fid[*it], x=fid[*(--it)];
//    cout<<x<<' '<<y<<endl;
    return dis[u]-dis[LCA(x, u)]-dis[LCA(y, u)]+dis[LCA(x, y)];
}

int main()
{
    int m;
    while(~scanf("%d%d", &n, &m))
    {
        init();
        for(int i=0; i<n-1; i++)
        {
            int u, v, w;
            scanf("%d%d%d", &u, &v, &w);
            AddEdge(u, v, w);
            AddEdge(v, u, w);
        }
        bfs(1);
        dfs(1, -1);
        LL ans=0;
        while(m--)
        {
            int u;
            scanf("%d", &u);
            if(S.find(id[u])==S.end())
            {
                ans+=get(u);
                printf("%lld\n", ans<<1);
//                cout<<(ans<<1)<<endl;
                S.insert(id[u]);
            }
            else
            {
                S.erase(id[u]);
                ans-=get(u);
                printf("%lld\n", ans<<1);
//                cout<<(ans<<1)<<endl;
            }
        }
    }
    return 0;
}
