#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <queue>
#include <vector>
#define mem(a, val) memset((a), (val), sizeof(a))
#define all(a) (a).begin(), (a).end()
using namespace std;
const int maxn=110;
int n, dis[maxn];
bool w[maxn][maxn];
vector<int> G[maxn];

void init()
{
    for(int i=1; i<=n; i++)
        G[i].clear();
    for(int i=1; i<=n; i++)
        for(int j=1; j<=n; j++)
            w[i][j]= i==j;
}

void floyd()
{
    for(int k=1; k<=n; k++)
        for(int i=1; i<=n; i++)
            for(int j=1; j<=n; j++)
                w[i][j]=(w[i][j] || (w[i][k] && w[k][j]));
}

bool spfa(int s)
{
    int cnt[maxn]={0}, d[maxn];
    mem(d, 0);
    d[s]=100;
    queue<int> q;
    while(!q.empty())q.pop();
    q.push(s);
    cnt[s]++;
    while(!q.empty())
    {
        int u=q.front();
        q.pop();
        if(cnt[u]>n)
        {
            if(w[u][n])return true;
            continue ;
        }
        for(int i=0; i<G[u].size(); i++)
        {
            int v=G[u][i];
            if(d[v]<d[u]+dis[v])
            {
                d[v]=d[u]+dis[v];
                q.push(v);
                ++cnt[v];
            }
        }
    }
    return d[n]>0;
}

int main()
{
    while(~scanf("%d", &n) && (~n))
    {
        init();
        for(int i=1; i<=n; i++)
        {
            scanf("%d", dis+i);
            int m, v;
            scanf("%d", &m);
            while(m--)
            {
                scanf("%d", &v);
                w[i][v]=true;
                G[i].push_back(v);
            }
        }
        floyd();
        if(w[1][n] && spfa(1))
            puts("winnable");
        else puts("hopeless");
    }
    return 0;
}
