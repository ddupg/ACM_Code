#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#define mem(a, val) memset((a), (val), sizeof(a))
using namespace std;
int n, k, vis[10], ans;
char s[10][10];
void dfs(int x, int deep)
{
    if(deep==k)
    {
        ans++;
        return ;
    }
    for(int i=x+1; i<n; i++)
        for(int j=0; j<n; j++)
            if(!vis[j] && s[i][j]=='#')
            {
                vis[j]=1;
                dfs(i, deep+1);
                vis[j]=0;
            }
}
int main()
{
    while(~scanf("%d%d", &n, &k) && ~n)
    {
        for(int i=0; i<n; i++)
            scanf("%s", s[i]);
        ans=0;
        mem(vis, 0);
        dfs(-1, 0);
        printf("%d\n", ans);
    }
    return 0;
}
