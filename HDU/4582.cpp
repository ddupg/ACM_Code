#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#define ALL(a) a.begin(), a.end()
#define clr(a, x) memset(a, x, sizeof a)
#define fst first
#define snd second
#define pb push_back
using namespace std;
typedef long long LL;
typedef pair<int, int> pii;
typedef pair<int, pii> piii;

const int maxn=2200;

int n, m, fa[maxn], deg[maxn];
bool used[maxn];
vector<int> G[maxn];
vector<piii> q;

void init()
{
    for(int i=0; i<=n; i++)
        G[i].clear();
    q.clear();
    clr(used, 0);
}

void dfs(int u, int f, int d)
{
    fa[u]=f, deg[u]=d;
    for(int i=0; i<G[u].size(); i++)
    {
        int v=G[u][i];
        if(v==f)continue ;
        dfs(v, u, d+1);
    }
}

int find(int u, int v)
{
    if(used[u])return -1;
    if(fa[u]==v)return u;
    return find(fa[u], v);
}

int main()
{
    while(~scanf("%d%d", &n, &m) && n+m)
    {
        init();
        for(int i=0; i<n-1; i++)
        {
            int u, v;
            scanf("%d%d", &u, &v);
            G[u].pb(v);
            G[v].pb(u);
        }
        dfs(1, -1, 0);
        for(int i=0; i<m-n+1; i++)
        {
            int u, v;
            scanf("%d%d", &u, &v);
            if(deg[u]<deg[v])swap(u, v);
            q.pb(piii(deg[v], pii(u, v)));
        }
        sort(ALL(q));
        reverse(ALL(q));
        int ans=0;
        for(int i=0; i<q.size(); i++)
        {
            int u=q[i].snd.fst, v=q[i].snd.snd;
            int x=find(u, v);
            if(~x)used[x]=true, ans++;
        }
        printf("%d\n", ans);
    }
    return 0;
}
