#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <set>
using namespace std;
const int maxn=1100;
int n, m, f[maxn];

void init()
{
    for(int i=1; i<=n; i++)
        f[i]=i;
}

int find(int x)
{
    return x==f[x]?x:f[x]=find(f[x]);
}

int main()
{
    int T;
    scanf("%d", &T);
    while(T--)
    {
        scanf("%d%d", &n, &m);
        init();
        while(m--)
        {
            int u, v;
            scanf("%d%d", &u, &v);
            u=find(u), v=find(v);
            f[u]=v;
        }

        set<int> S;

        for(int i=1; i<=n; i++)
            S.insert(find(i));
        printf("%d\n", S.size());
    }
    return 0;
}
