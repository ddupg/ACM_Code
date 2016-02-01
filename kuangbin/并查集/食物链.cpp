#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
using namespace std;
const int maxn=50000+100;

int n, m, f[maxn];

void init()
{
    for(int i=1; i<=n+10; i++)
        f[i]=i;
}

int find(int x)
{
    return x==f[x]?x:f[x]=find(f[x]);
}

int main()
{
    while(~scanf("%d%d", &n, &m))
    {
        init();
        int ans=0;
        while(m--)
        {
            int op, x, y, flag=1;
            scanf("%d%d%d", &op, &x, &y);
            x+=3, y+=3;
            int u=find(x), v=find(y);


        }
        printf("%d\n", ans);
    }
    return 0;
}
