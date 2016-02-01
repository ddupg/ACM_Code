#include <cstdio>
#include <iostream>
#include <cstring>
#include <sstream>
using namespace std;
const int maxn=1010;
struct Edge
{
    int v, nxt;
} edge[maxn*maxn];

int link[maxn][maxn], head[maxn], tot;
bool used[maxn];
int num[maxn];

void init()
{
    memset(head, -1, sizeof head);
    tot=0;
}
void AddEdge(int u, int v)
{
    edge[tot].v=v;
    edge[tot].nxt=head[u];
    head[u]=tot++;
}

bool dfs(int u)
{
    for(int i=head[u]; ~i; i=edge[i].nxt)
    {
        int v=edge[i].v;
        if(used[v])continue ;
        used[v]=1;
        if(link[v][0]<num[v])
        {
            link[v][++link[v][0]]=u;
            return true;
        }
        for(int i=1; i<=num[v]; i++)
            if(dfs(link[v][i]))
            {
                link[v][i]=u;
                return true;
            }
    }
    return false;
}

int hungary(int n, int limit)
{
    int ans=0;
    for(int i=1; i<=n; i++)
    {
        link[i][0]=0;
        num[i]=limit;
    }
    for(int u=1; u<=n; u++)
    {
        memset(used, 0, sizeof used);
        ans+=dfs(u);
    }
    return ans;
}
int main()
{
    int n, m;
    char s[10000];
    while(~scanf("%d%d", &n, &m) && n+m)
    {
        init();
        getchar();
        for(int i=1; i<=n; i++)
        {
            gets(s);
            stringstream ss(s);
            ss>>s;
            int v;
            while(ss>>v)
                AddEdge(i, v+1);
        }
        int L=1, R=n;
        while(L<R)
        {
            int mid=(L+R)>>1;
            if(hungary(n, mid)==n)
                R=mid;
            else L=mid+1;
        }
        printf("%d\n", L);
    }
    return 0;
}
