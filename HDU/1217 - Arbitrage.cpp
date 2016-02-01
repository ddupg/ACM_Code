#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <queue>
#include <vector>
#include <map>
using namespace std;
const int maxn=33;
double w[maxn][maxn];
map<string, int> g;
vector<int> G[maxn];
int n, vis[maxn];
void init()
{
    for(int i=1; i<=n; i++)
        G[i].clear();
    g.clear();
    memset(vis, 0, sizeof(vis));
}

bool spfa(int s)
{
    queue<int> q;
    q.push(s);
    vis[s]=1;
    double d[maxn]={0.0};
    d[s]=100;
    while(!q.empty())
    {
        int u=q.front();
        q.pop();
        if(vis[u]>n)return 1;
        for(int i=0; i<G[u].size(); i++)
        {
            int v=G[u][i];
            if(d[v]<d[u]*w[u][v])
            {
                d[v]=d[u]*w[u][v];
                q.push(v);
                vis[v]++;
            }
        }
    }
    return 0;
}

int main()
{
    int kase=0, m;
    double rate;
    char s1[100], s2[100];
    while(~scanf("%d", &n) && n)
    {
        init();
        for(int i=1; i<=n; i++)
        {
            scanf("%s", s1);
            g[s1]=i;
        }
        scanf("%d", &m);
        while(m--)
        {
            scanf("%s%lf%s", s1, &rate, s2);
            w[g[s1]][g[s2]]=rate;
            G[g[s1]].push_back(g[s2]);
        }
        printf("Case %d: %s\n", ++kase, spfa(1)?"Yes":"No");
    }
    return 0;
}
