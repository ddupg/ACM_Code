#include <bits/stdc++.h>
using namespace std;

const int maxn=200000+100;
const int DEG=20;

int n, m, fa[maxn][DEG], pre[maxn], deg[maxn];
long long pw[maxn];
vector<int> G[maxn];

struct Edge
{
    int v;
    long long w;
} E[maxn<<1];

int find(int x)
{
    return pre[x]==x?x:pre[x]=find(pre[x]);
}

void init()
{
    for(int i=0; i<=n; i++)
        pre[i]=i;

    queue<int> q;
    fa[1][0]=1;
    deg[1]=0;
    q.push(1);
    while(!q.empty())
    {
        int u=q.front();
        q.pop();
        for(int i=1; i<DEG; i++)
            fa[u][i]=fa[fa[u][i-1]][i-1];
        for(int i=0; i<G[u].size(); i++)
        {
            int v=E[G[u][i]].v;
            long long w=E[G[u][i]].w;
            if(v==fa[u][0])continue ;
            fa[v][0]=u;
            deg[v]=deg[u]+1;
            pw[v]=w;
            q.push(v);
        }
    }
}

int LCA(int u, int v)
{
    if(deg[u]<deg[v])swap(u, v);
    for(int det=deg[u]-deg[v], i=0; det; i++, det>>=1)
        if(det&1)
            u=fa[u][i];
    if(u==v)return u;
    for(int i=DEG-1; i>=0; i--)
        if(fa[u][i]!=fa[v][i])
            u=fa[u][i], v=fa[v][i];
    return fa[u][0];
}

long long query(int u, int x, long long val)
{
    for(; deg[u]>deg[x] && val; )
    {
        if(pw[u]!=1)
        {
            val/=pw[u];
            u=fa[u][0];
        }
        else u=find(u);
    }
    return val;
}

int main()
{
    scanf("%d%d", &n, &m);
    for(int i=0; i<n-1; i++)
    {
        int u, v;
        long long w;
        scanf("%d%d%I64d", &u, &v, &w);
        E[i<<1].v=v, E[i<<1].w=w;
        G[u].push_back(i<<1);
        E[i<<1|1].v=u, E[i<<1|1].w=w;
        G[v].push_back(i<<1|1);
    }

    init();
    for(int i=2; i<=n; i++)
        if(pw[i]==1)
            pre[i]=fa[i][0];

    while(m--)
    {
        int op;
        scanf("%d", &op);
        if(op==1)
        {
            int u, v;
            long long val;
            scanf("%d%d%I64d", &u, &v, &val);
            int x=LCA(u, v);
            val=query(u, x, val);
            val=query(v, x, val);
            printf("%I64d\n", val);
        }
        else
        {
            int x;
            long long y;
            scanf("%d%I64d", &x, &y);
            x=((x-1)<<1);
            int u=E[x].v, v=E[x^1].v;
            if(fa[u][0]==v)
                swap(u, v);
            pw[v]=y;
            if(y==1) pre[v]=u;
        }
    }
    return 0;
}
