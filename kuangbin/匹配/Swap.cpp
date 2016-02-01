#include <cstdio>
#include <cstring>
#include <vector>
using namespace std;
const int maxn=110;
struct Edge
{
    int to, nxt;
} edge[maxn*maxn];
int head[maxn], tot;
void init()
{
    tot=0;
    memset(head, -1, sizeof head);
}
void AddEdge(int u, int v)
{
    edge[tot].to=v;
    edge[tot].nxt=head[u];
    head[u]=tot++;
}
int n, link[maxn], x[maxn];
bool used[maxn];

bool dfs(int u)
{
    for(int i=head[u]; ~i; i=edge[i].nxt)
    {
        int v=edge[i].to;
        if(!used[v])
        {
            used[v]=true;
            if(link[v]==-1 || dfs(link[v]))
            {
                link[v]=u;
                x[u]=v;
                return true;
            }
        }
    }
    return false;
}

int hungary()
{
    int ans=0;
    memset(link, -1, sizeof link);
    for(int u=1; u<=n; u++)
    {
        memset(used, 0, sizeof used);
        ans+=dfs(u);
    }
    return ans;
}

int main()
{
    while(~scanf("%d", &n))
    {
        init();
        for(int i=1; i<=n; i++)
            for(int j=1; j<=n; j++)
            {
                int t;
                scanf("%d", &t);
                if(t)AddEdge(i, j);
            }
        if(hungary()!=n)
        {
            puts("-1");
            continue ;
        }
        vector<pair<int, int> > ans;
        for(int i=1; i<=n; i++)
        {
            if(link[i]==i)continue ;
            ans.push_back(make_pair(i, link[i]));
            link[x[i]]=link[i];
            swap(x[i], x[link[i]]);
        }
        printf("%d\n", ans.size());
        for(int i=0; i<ans.size(); i++)
            printf("R %d %d\n", ans[i].first, ans[i].second);
    }
    return 0;
}
