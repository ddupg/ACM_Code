#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <stack>
#include <vector>
using namespace std;

const int maxn=1010;
struct Edge
{
    int v, nxt;
} edge[maxn*maxn];
int head[maxn], tot;

void init()
{
    tot=0;
    memset(head, -1, sizeof head);
}
void AddEdge(int u, int v)
{
    edge[tot].v=v;
    edge[tot].nxt=head[u];
    head[u]=tot++;
}
int N, link[maxn], match[maxn];
bool used[maxn];

bool dfs(int u)
{
    for(int i=head[u]; ~i; i=edge[i].nxt)
    {
        int v=edge[i].v;
        if(!used[v])
        {
            used[v]=true;
            if(link[v]==-1 || dfs(link[v]))
            {
                link[v]=u;
                match[u]=v;
                return true;
            }
        }
    }
    return false;
}
int hungary()
{
    int ans=0;
    memset(link, -1, sizeof link);
    memset(match, -1, sizeof match);
    for(int u=1; u<=N; u++)
    {
        memset(used, 0, sizeof used);
        ans+=dfs(u);
    }
    return ans;
}

struct Tarjan
{
    Edge edge[maxn*maxn];
    int pre[maxn], low[maxn],dfn, scc, bel[maxn];
    int head[maxn], tot;
    bool ins[maxn];
    stack<int> S;
    void init()
    {
        memset(head, -1, sizeof head);
        memset(pre, 0, sizeof pre);
        memset(ins, 0, sizeof ins);
        memset(bel, 0, sizeof bel);
        tot=dfn=scc=0;
    }
    void AddEdge(int u, int v)
    {
        edge[tot].v=v;
        edge[tot].nxt=head[u];
        head[u]=tot++;
    }
    void tarjan(int u)
    {
        pre[u]=low[u]=++dfn;
        S.push(u);
        ins[u]=1;
        for(int i=head[u]; ~i; i=edge[i].nxt)
        {
            int v=edge[i].v;
            if(!pre[v])
            {
                tarjan(v);
                low[u]=min(low[u], low[v]);
            }
            else if(ins[v])
                low[u]=min(low[u], pre[v]);
        }
        if(low[u]==pre[u])
        {
            ++scc;
            while(true)
            {
                int v=S.top();
                S.pop();
                ins[v]=false;
                bel[v]=scc;
                if(v==u)break;
            }
        }
    }
    void solve(int n)
    {
        for(int i=1; i<=n; i++)
            if(!pre[i])
                tarjan(i);
    }
} SCC;

int main()
{
    int T, kase=0;
    int n, m;
    scanf("%d", &T);
    while(T--)
    {
        scanf("%d%d", &n, &m);
        init();
        N=n;
        for(int i=1; i<=n; i++)
        {
            int mm, v;
            scanf("%d", &mm);
            while(mm--)
            {
                scanf("%d", &v);
                AddEdge(i, v);
            }
        }
        int cnt=hungary();
        N=n+m-cnt;
        for(int i=n+1; i<=N; i++)
            for(int j=1; j<=N; j++)
                AddEdge(i, j);
        for(int j=m+1; j<=N; j++)
            for(int i=1; i<=N; i++)
                AddEdge(i, j);
        hungary();
        SCC.init();
        for(int u=1; u<=N; u++)
            for(int i=head[link[u]]; ~i; i=edge[i].nxt)
            {
                int v=edge[i].v;
                if(v==u)continue ;
                SCC.AddEdge(u, v);
            }
        printf("Case #%d:\n", ++kase);
        SCC.solve(N);
        for(int p=1; p<=n; p++)
        {
            int u=match[p], num=SCC.bel[u];
            vector<int> ans;
            ans.clear();
            for(int i=head[p]; ~i; i=edge[i].nxt)
            {
                int v=edge[i].v;
                if(SCC.bel[v]==num && v<=m)
                    ans.push_back(v);
            }
            sort(ans.begin(), ans.end());
            printf("%d", ans.size());
            for(int i=0; i<ans.size(); i++)
                printf(" %d", ans[i]);
            puts("");
        }
    }
    return 0;
}
