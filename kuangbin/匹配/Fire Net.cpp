#include <iostream>
#include <cstdio>
#include <cstring>
#define mem(a, val) memset(a, val, sizeof a)
using namespace std;
const int maxn=20;

char mp[10][10];

int n, m, tot, linker[maxn];
bool used[maxn], g[maxn][maxn];

bool match(int u)
{
    for(int v=1; v<=n; v++)if(g[u][v])
        {
            if(used[v])continue ;
            used[v]=true;
            if(linker[v]==-1 || match(linker[v]))
            {
                linker[v]=u;
                return true;
            }
        }
    return false;
}

int hungary()
{
    mem(linker, -1);
    int ans=0;
    for(int i=1; i<=n; i++)
    {
        mem(used, 0);
        ans+=match(i);
    }
    return ans;
}

int main()
{
    while(~scanf("%d", &m) && m)
    {
        n=m*m;
        int id1[maxn][maxn], id2[maxn][maxn];
        for(int i=1; i<=m; i++)
            scanf("%s", mp[i]+1);
        mem(id1, -1);
        mem(id2, -1);
        int cnt=1;
        for(int i=1; i<=m; i++)
        {
            for(int j=1; j<=m; j++)
            {
                while(mp[i][j]!='X' && mp[i][j])
                    id1[i][j]=cnt, j++;
                cnt++;
            }
        }
        cnt=1;
        for(int j=1; j<=m; j++)
        {
            for(int i=1; i<=m; i++)
            {
                while(mp[i][j]!='X' && mp[i][j])
                    id2[i][j]=cnt, i++;
                cnt++;
            }
        }
        mem(g, 0);
        for(int i=1; i<=m; i++)
            for(int j=1; j<=m; j++)
                if(~id1[i][j] && ~id2[i][j])
                    g[id1[i][j]][id2[i][j]]=1;
        printf("%d\n", hungary());
    }
    return 0;
}
