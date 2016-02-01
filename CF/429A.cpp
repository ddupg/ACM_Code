#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;
const int maxn=100000+10;

int n, col[maxn], init[maxn], to[maxn];
vector<int> G[maxn], ans;

void solve(int x, int pre)
{
    if(col[x]==1 || col[x]==3)
        init[x]^=1;
    if(init[x]!=to[x])
    {
        ans.push_back(x);
        if(col[x]==1)
            col[x]=0;
        else if(col[x]==2)
            col[x]=3;
        else if(col[x]==3)
            col[x]=2;
        else col[x]=1;
    }
    int op=0;
    if(col[x]==1)
        op=2;
    else if(col[x]==2)
        op=1;
    else if(col[x]==3)
        op=3;
    for(int i=0; i<G[x].size(); i++)
    {
        int u=G[x][i];
        if(u==pre)continue ;
        col[u]=op;
        solve(u, x);
    }
}

int main()
{
    scanf("%d", &n);
    for(int i=0; i<n-1; i++)
    {
        int u, v;
        scanf("%d%d", &u, &v);
        G[u].push_back(v);
        G[v].push_back(u);
    }
    for(int i=1; i<=n; i++)
        scanf("%d", init+i);
    for(int i=1; i<=n; i++)
        scanf("%d", to+i);
    solve(1, -1);
    printf("%d\n", ans.size());
    for(int i=0; i<ans.size(); i++)
        printf("%d\n", ans[i]);
    return 0;
}
