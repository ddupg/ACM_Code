#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn=10000+10;
int n, a[maxn];
bool vis[maxn];

int main()
{
    while(~scanf("%d", &n) && n)
    {
        getchar();
        int ok=1;
        memset(vis, 0, sizeof vis);
        for(int i=0; i<n; i++)
        {
            scanf("%d", a+i);
            vis[a[i]]=true;
            int len=min(a[i]-1, n-a[i]-1);
            for(int j=1; j<=len && ok; j++)
            {
                int u=a[i]-j, v=a[i]+j;
                if((vis[u] && !vis[v]) || (vis[v] && !vis[u]))
                    ok=0;
            }
        }
        puts(ok?"yes":"no");
    }
    return 0;
}
