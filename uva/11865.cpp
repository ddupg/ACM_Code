#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
const int INF = 0x3f3f3f3f;
const int MAXN = 1010;
const int MAXM = 40010;
struct Edge
{
    int u, v, cost, kbps;
};
Edge edge[MAXM], e[MAXM];
int pre[MAXN],id[MAXN],visit[MAXN],in[MAXN];
int zhuliu(int root,int n,int m)
{
    int res = 0,u,v;
    while(1)
    {
        for(int i = 0; i < n; i++)
            in[i] = INF;
        for(int i = 0; i < m; i++)
            if(edge[i].u != edge[i].v && edge[i].cost < in[edge[i].v])
            {
                pre[edge[i].v] = edge[i].u;
                in[edge[i].v] = edge[i].cost;
            }
        for(int i = 0; i < n; i++)
            if(i != root && in[i] == INF)
                return INF;
        int tn = 0;
        memset(id,-1,sizeof(id));
        memset(visit,-1,sizeof(visit));
        in[root] = 0;
        for(int i = 0; i < n; i++)
        {
            res += in[i];
            v = i;
            while( visit[v] != i && id[v] == -1 && v != root)
            {
                visit[v] = i;
                v = pre[v];
            }
            if( v != root && id[v] == -1 )
            {
                for(int u = pre[v]; u != v ; u = pre[u])
                    id[u] = tn;
                id[v] = tn++;
            }
        }
        if(tn == 0)break;
        for(int i = 0; i < n; i++)
            if(id[i] == -1)
                id[i] = tn++;
        for(int i = 0; i < m;)
        {
            v = edge[i].v;
            edge[i].u = id[edge[i].u];
            edge[i].v = id[edge[i].v];
            if(edge[i].u != edge[i].v)
                edge[i++].cost -= in[v];
            else
                swap(edge[i],edge[--m]);
        }
        n = tn;
        root = id[root];
    }
    return res;
}
int g[MAXN][MAXN], n,m, SumCost;

bool build(int cur)
{
    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            g[i][j] = INF;
    int u,v,cost;
    for(int i=0; i<m; i++)
    {
        u=e[i].u, v=e[i].v, cost=e[i].cost;
        if(u == v || e[i].kbps<cur)continue;
        g[u][v] = min(g[u][v],cost);
    }
    int L = 0;
    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            if(g[i][j] < INF)
            {
                edge[L].u = i;
                edge[L].v = j;
                edge[L++].cost = g[i][j];
            }
    int ans = zhuliu(0, n, L);
    return ans<=SumCost;
}

int main()
{
    int T;
    scanf("%d", &T);
    while( T-- )
    {
        scanf("%d%d%d", &n, &m, &SumCost);
        vector<int> v;
        v.clear();
        for(int i=0; i<m; i++)
        {
            scanf("%d%d%d%d", &e[i].u, &e[i].v, &e[i].kbps, &e[i].cost);
            v.push_back(e[i].kbps);
        }
        sort(v.begin(), v.end());
        int L=0, R=unique(v.begin(), v.end())-v.begin()-1;
        if(!build(v[0]))
        {
            puts("streaming not possible.");
            continue ;
        }
        while(L<R)
        {
            int mid=(L+R+1)>>1;
            if(build(v[mid]))
                L=mid;
            else R=mid-1;
        }
        printf("%d kbps\n", v[L]);
    }
    return 0;
}
