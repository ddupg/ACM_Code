#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <stack>
using namespace std;
const int maxn=110;

vector<int> G[maxn], belong[maxn];
int pre[maxn], link[maxn], sccno[maxn], dfn, scc;
stack<int> S;

void dfs(int u)
{
    pre[u]=link[u]=++dfn;
    S.push(u);
    for(int i=0; i<G[u].size(); i++)
    {
        int v=G[u][i];
        if(!pre[v])
        {
            dfs(v);
            link[u]=min(link[u], link[v]);
        }
        else if(!sccno[v])
            link[u]=min(link[u], pre[v]);
    }
    if(link[u]==pre[u])
    {
        scc++;
        while(true)
        {
            int x=S.top();
            S.pop();
            belong[scc].push_back(x);
            sccno[x]=scc;
            if(x==u)break;
        }
    }
}

void find_scc(int n)
{
    dfn=scc=0;
    memset(sccno, 0, sizeof sccno);
    memset(pre, 0, sizeof pre);
    for(int i=1; i<=n; i++)
        if(!pre[i])
            dfs(i);
}

int main()
{
    int n, u;
    scanf("%d", &n);
    for(int i=1; i<=n; i++)
        while(scanf("%d", &u) && u)
            G[i].push_back(u);
    find_scc(n);
    int in0[maxn]={0}, out0[maxn]={0};
    for(int i=1; i<=n; i++)
        for(int j=0; j<G[i].size(); j++)
            if(sccno[i]!=sccno[G[i][j]])
                out0[sccno[i]]=in0[sccno[G[i][j]]]=1;
    int a=0, b=0;
    for(int i=1; i<=scc; i++)
    {
        if(!in0[i])
            a++;
        if(!out0[i])
            b++;
    }
    if(scc==1)
        puts("1\n0");
    else
        printf("%d\n%d\n", a, max(a, b));
    return 0;
}
