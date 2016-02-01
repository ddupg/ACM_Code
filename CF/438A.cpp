#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <set>
using namespace std;
typedef long long LL;
const int maxn=1010;

int n, m, val[maxn];

int main()
{
    scanf("%d%d", &n, &m);
    for(int i=1; i<=n; i++)
        scanf("%d", val+i);
    LL ans=0;
    while(m--)
    {
        int u, v;
        scanf("%d%d", &u, &v);
        ans+=min(val[u], val[v]);
    }
    printf("%I64d\n", ans);
}
