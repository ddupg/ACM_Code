#include <iostream>
#include <cstring>
#include <algorithm>
#include <cstdio>
#define clr(a, x) memset(a, x, sizeof a)
#define pb push_back
using namespace std;
typedef pair<int, int> pii;

const int maxn=3033;
const int oo=0x3f3f3f3f;

int n, g[maxn][maxn], fa[maxn], d[maxn], pre[maxn];
bool vis[maxn];
int ise[maxn][maxn];
vector<int> G[maxn];
int q[maxn], head, tail;

void init()
{
    for(int i=1; i<=n; i++)
        G[i].clear();
    clr(vis, 0);
    clr(ise, 0);
}

void Prim()
{
    for(int i=1; i<=n; i++)
        pre[i]=1, d[i]=g[1][i];
    clr(vis, 0);
    vis[1]=true;
    for(int i=0; i<n-1; i++)
    {
        int mx=oo, x;
        for(int u=1; u<=n; u++)
            if(!vis[u] && d[u]<mx)
                mx=d[x=u];
        vis[x]=true;
        G[pre[x]].pb(x);
        G[x].pb(pre[x]);
        ise[x][pre[x]]=ise[pre[x]][x]=1;
        for(int i=1; i<=n; i++)
            if(x!=i && d[i]>g[x][i])
                d[i]=g[x][i], pre[i]=x;
    }
}

void solve(int rt)
{
    head=tail=0;
    q[tail++]=rt;
    pre[rt]=-1;
    while(head!=tail)
    {
        int u=q[head++];
        for(int i=0; i<G[u].size(); i++)
        {
            int v=G[u][i];
            if(v==pre[u])continue ;
            pre[v]=u;
            q[tail++]=v;
        }
    }
    clr(d, 0x3f);
    for(int i=1; i<=n; i++)
        if(i!=rt && !ise[rt][i])
            d[i]=min(d[i], g[rt][i]);
    for(int i=head-1; i>=0; i--)
    {
        int u=q[i];
        for(int j=0; j<G[u].size(); j++)
        {
            int v=G[u][j];
            if(v==pre[u]) continue ;
            d[u]=min(d[u], d[v]);
        }
        if(pre[u]==-1)continue ;
        if(g[pre[u]][u]==d[u])
            ise[pre[u]][u]=ise[u][pre[u]]=2;
    }
}

int main()
{
    int T;
    scanf("%d", &T);
    while(T--)
    {
        scanf("%d", &n);
        init();
        for(int i=1; i<=n; i++)
            for(int j=1; i+j<=n; j++)
                scanf("%d", &g[i][i+j]), g[i+j][i]=g[i][i+j];
        Prim();
        for(int i=1; i<=n; i++)
            solve(i);
        int cnt=0;
        for(int u=1; u<=n; u++)
            for(int i=0; i<G[u].size(); i++)
                if(ise[u][G[u][i]]==1)cnt++;
        printf("%d\n", cnt>>1);
    }
    return 0;
}
