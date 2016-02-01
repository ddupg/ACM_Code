#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <stack>
using namespace std;
typedef long long LL;
const int maxn=100000+100;
const int oo=0x3f3f3f3f;

struct Edge
{
    int v, nxt;
} edge[maxn*2];

int n, m, pre[maxn], low[maxn], dfn, scc, belong[maxn], num[maxn], out[maxn], in[maxn];
int head[maxn], e;
bool ins[maxn];
stack<int> S;

void init()
{
    memset(pre, 0, sizeof pre);
    memset(head, -1, sizeof head);
    memset(ins, 0, sizeof ins);
    memset(belong, 0, sizeof belong);
    memset(num, 0, sizeof num);
    memset(out, 0, sizeof out);
    memset(in, 0, sizeof in);
    e=dfn=scc=0;
}

void AddEdge(int u, int v)
{
    edge[e].v=v;
    edge[e].nxt=head[u];
    head[u]=e++;
}

void Tarjan(int u)
{
    pre[u]=low[u]=++dfn;
    S.push(u);
    ins[u]=true;
    for(int i=head[u]; ~i; i=edge[i].nxt)
    {
        int v=edge[i].v;
        if(!pre[v])
        {
            Tarjan(v);
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
            num[scc]++;
            belong[v]=scc;
            if(v==u)break;
        }
    }
}

void solve()
{
    if(scc==1)
    {
        puts("-1");
        return ;
    }
    LL ans=0;
    for(int i=1; i<=n; i++)
        for(int j=head[i]; ~j; j=edge[j].nxt)
            if(belong[i]!=belong[edge[j].v])
                out[belong[i]]++, in[belong[edge[j].v]]++;
    int tmp=oo;
    for(int i=1; i<=scc; i++)
        if(!out[i] || !in[i])
            tmp=min(tmp, num[i]);
    ans=(LL)(n-tmp)*n+(LL)(tmp*tmp)-n-e;
    printf("%I64d\n", ans);
}

int main()
{
    int T, kase=0;
    scanf("%d", &T);
    while(T--)
    {
        scanf("%d%d", &n, &m);
        init();
        while(m--)
        {
            int u, v;
            scanf("%d%d", &u, &v);
            AddEdge(u, v);
        }
        for(int i=1; i<=n; i++)
            if(!pre[i])
                Tarjan(i);
        printf("Case %d: ", ++kase);
        solve();
    }
    return 0;
}
