#include <iostream>
#include <cstdio>
#include <map>
#include <cstring>
#include <vector>
using namespace std;
const int maxn=2200;
#define F first
#define S second
typedef pair<int, int> pii;
map<string, int> g;
char sg[maxn][25];

int n, vis[maxn], tot=0, next[maxn];
vector<int> v[maxn];

int getid(char* s)
{
    if(g.count(s))
        return g[s];
    g[s]=++tot;
    strcpy(sg[tot], s);
    return tot;
}

int dfs(int u)
{
    vis[u]=true;
    if(!next[u])return u;
    return dfs(next[u]);
}

int main()
{
    g.clear();
    scanf("%d", &n);
    while(n--)
    {
        char s1[25], s2[25];
        scanf("%s%s", s1, s2);
        int id1=getid(s1), id2=getid(s2);
        next[id1]=id2;
    }
    vector<pii> ans;
    for(int i=1; i<=tot; i++)
        if(!vis[i])
        {
            vis[i]=true;
            ans.push_back(make_pair(i, dfs(next[i])));
        }

    printf("%d\n", ans.size());
    for(int i=0; i<ans.size(); i++)
        printf("%s %s\n", sg[ans[i].F], sg[ans[i].S]);
    return 0;
}
