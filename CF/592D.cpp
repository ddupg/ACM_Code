#include <bits/stdc++.h>
using namespace std;

const int maxn=130000;
const int oo=0x3f3f3f3f;

int n, m, ans=0, rt;
pair<int, int> mx(-oo, -oo);
set<int> G[maxn];
bool was[maxn];

bool dfs_delete(int u, int f)
{
    bool ok=false;
    for(set<int>::iterator it=G[u].begin(), i; it!=G[u].end(); )
    {
        i=it++;
        int v=*i;
        if(v==f)continue ;
        if(!dfs_delete(v, u))
            G[u].erase(i);
        else ok=true;
    }
    return (ok || was[u]);
}
void dfs_cal(int u, int f)
{
    for(auto v : G[u])
        if(v!=f)
        {
            ans+=2;
            dfs_cal(v, u);
        }
}
pair<int, int> dfs_solve(int u, int f, int d)
{
    mx=max(mx, make_pair(d, -min(u, rt)));
    pair<int, int> res(0, -u);
    for(auto v : G[u])
    {
        if(v==f)continue ;
        pair<int, int>tmp=dfs_solve(v, u, d+1);
        mx=max(mx, make_pair(res.first+tmp.first, max(res.second, tmp.second)));
        res=max(res, tmp);
    }
    return make_pair(res.first+1, res.second);
}

int main()
{
    scanf("%d%d", &n, &m);
    for(int i=0; i<n-1; i++)
    {
        int u, v;
        scanf("%d%d", &u, &v);
        G[u].insert(v);
        G[v].insert(u);
    }
    for(int i=0; i<m; i++)
    {
        int x;
        scanf("%d", &x);
        was[rt=x]=true;
    }
    dfs_delete(rt, -1);
    dfs_cal(rt, -1);
    dfs_solve(rt, -1, 0);
    printf("%d\n%d\n", -mx.second, ans-mx.first);
    return 0;
}
