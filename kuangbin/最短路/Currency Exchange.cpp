#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;
const int maxn=111;

vector<int> G[maxn];
int n, m, T;
double R[maxn][maxn], C[maxn][maxn], d[maxn];

void init()
{
    for(int i=1; i<=n; i++)
        G[i].clear();
    memset(d, 0, sizeof(d));
}

double spfa()
{
    queue<int> q;
    int vis[maxn]= {0};
    for(int i=0; i<G[T].size(); i++)
    {
        int v=G[T][i];
        if(d[v]<(d[T]-C[T][v])*R[T][v])
        {
            d[v]=(d[T]-C[T][v])*R[T][v];
            if(!vis[v])
            {
                vis[v]=true;
                q.push(v);
            }
        }
    }
    while(!q.empty())
    {
        int u=q.front();
        q.pop();
        vis[u]=false;
        for(int i=0; i<G[u].size(); i++)
        {
            int v=G[u][i];
            if(d[v]<(d[u]-C[u][v])*R[u][v])
            {
                d[v]=(d[u]-C[u][v])*R[u][v];
                if(!vis[v])
                {
                    vis[v]=true;
                    q.push(v);
                }
            }
        }
    }
    return d[T];
}

int main()
{
    double rate;
    while(~scanf("%d%d%d%lf", &n, &m, &T, &rate))
    {
        init();
        d[T]=rate;
        while(m--)
        {
            int u, v;
            scanf("%d%d", &u, &v);
            G[u].push_back(v);
            G[v].push_back(u);
            scanf("%lf%lf%lf%lf", &R[u][v], &C[u][v], &R[v][u], &C[v][u]);
        }
        puts(spfa()>rate?"YES":"NO");
    }
    return 0;
}
