#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <stack>
#define pb push_back
using namespace std;
typedef long long LL;

const int maxn=100000+100;
const int N=200000+100;

int n, m, ans[maxn], val[maxn], dfn[maxn], fdfn[maxn], tot;
int id[N*10], pr[N*10];
bool vis[N*10];
stack<int> stk[N];
vector<int> G[maxn], qry[maxn];

void init()
{
    int idx=0;
    for(int i=2; i<=2000000; i++)if(!vis[i])
        {
            id[i]=++idx;
            for(int j=i; j<=2000000; j+=i)
                vis[j]=true, pr[j]=i;
        }
}

void dfs(int u, int f)
{
    dfn[u]=++tot;
    fdfn[tot]=u;
    int res=-1, mx=-1;
    for(int t=val[u]; t>1; )
    {
        int x=pr[t], y=id[x];
        if(!stk[y].empty() && mx<stk[y].top())
            res=fdfn[mx=stk[y].top()];
        stk[y].push(dfn[u]);
        while(t%x==0)t/=x;
    }
    for(int i=0; i<qry[u].size(); i++)
        ans[qry[u][i]]=res;
    for(int i=0; i<G[u].size(); i++)
    {
        int v=G[u][i];
        if(v==f)continue ;
        dfs(v, u);
    }
    for(int t=val[u]; t>1; )
    {
        int x=pr[t], y=id[x];
        stk[y].pop();
        while(t%x==0)t/=x;
    }
}

int main()
{
    init();
    scanf("%d%d", &n, &m);
    for(int i=1; i<=n; i++)
        scanf("%d", val+i);
    for(int i=0; i<n-1; i++)
    {
        int u, v;
        scanf("%d%d", &u, &v);
        G[u].pb(v);
        G[v].pb(u);
    }
    for(int i=0; i<m; i++)
    {
        int op, x;
        scanf("%d%d", &op, &x);
        if(op==1)qry[x].pb(i), ans[i]=-1;
        else
        {
            tot=0;
            dfs(1, -1);
            for(int i=1; i<=n; i++)
                qry[i].clear();
            scanf("%d", val+x);
            ans[i]=0;
        }
    }
    tot=0;
    dfs(1, -1);
    for(int i=0; i<m; i++)if(ans[i])
        printf("%d\n", ans[i]);
    return 0;
}
