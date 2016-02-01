#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn=100010;

int n, tm, d[maxn][12], cnt[maxn][12];

int dp()
{
    memset(d, 0, sizeof d);
    for(int t=tm; t>=0; t--)
        for(int x=0; x<=10; x++)
            for(int i=max(0, x-1); i<=min(10, x+1); i++)
                d[t][x]=max(d[t][x], d[t+1][i]+cnt[t][x]);
    return d[0][5];
}

int main()
{
    while(~scanf("%d", &n) && n)
    {
        memset(cnt, 0, sizeof cnt);
        int x, t;
        tm=0;
        for(int i=0; i<n; i++)
        {
            scanf("%d%d", &x, &t);
            ++cnt[t][x];
            tm=max(tm, t);
        }
        printf("%d\n", dp());
    }
    return 0;
}
