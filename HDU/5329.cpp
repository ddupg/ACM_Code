#pragma comment(linker, "/STACK:1024000000,1024000000")
#include <cstdio>
#include <cstring>
#include <vector>
#define ALL(a) a.begin(), a.end()
#define clr(a, x) memset(a, x, sizeof a)
#define pb push_back
using namespace std;

const int maxn=100000+100;

int n, cir[maxn], cnt, sz[maxn], num[maxn];
vector<int> G[maxn];
bool incir[maxn], vis[maxn];
int fa[maxn];

void init()
{
    for(int i=1; i<=n; i++)
    {
        G[i].clear();
        vis[i]=incir[i]=0;
        fa[i]=i;
        sz[i]=0;
    }
    cnt=0;
}

int find(int x)
{
    return x==fa[x]?x:fa[x]=find(fa[x]);
}

bool find_cir(int u, int f, int T)
{
    if(u==T)
        return true;
    vis[u]=true;
    for(int i=0; i<G[u].size(); i++)
    {
        int v=G[u][i];
        if(v==f)continue ;
        if(find_cir(v, u, T))
        {
            cir[++cnt]=u;
            incir[u]=true;
            return true;
        }
    }
    return false;
}

int dfs(int u, int f)
{
    sz[u]=1;
    for(int i=0; i<G[u].size(); i++)
    {
        int v=G[u][i];
        if(v==f || incir[v])continue ;
        sz[u]+=dfs(v, u);
    }
    return sz[u];
}

bool solve(int k)
{
    int tot=0, ans=0, s=0;
    for(int u=1; u<=n; u++)
        if(!incir[u] && sz[u]%k==0)tot++;
    clr(num, 0);
    for(int i=1; i<=cnt; i++)
    {
        int u=cir[i];
        s=(s+sz[u])%k;
        ++num[s];
        ans=max(ans, tot+num[s]);
    }
    return ans==n/k;
}

int main()
{
    while(~scanf("%d", &n))
    {
        init();
        int S=-1, T;
        for(int u=1, v; u<=n; u++)
        {
            scanf("%d", &v);
            G[u].pb(v);
            G[v].pb(u);
            if(S==-1)
            {
                int tu=find(u), tv=find(v);
                if(tu==tv)S=u, T=v;
                else fa[tu]=tv;
            }
        }
        cir[++cnt]=T;
        incir[T]=true;
        find_cir(S, -1, T);
        for(int i=1; i<=cnt; i++)
            dfs(cir[i], -1);
        int ans=0;
        for(int i=1; i*i<=n; i++)
            if(n%i==0)
            {
                if(solve(i))ans++;
                if(i*i!=n && solve(n/i))ans++;
            }
        printf("%d\n", ans);
    }
    return 0;
}
