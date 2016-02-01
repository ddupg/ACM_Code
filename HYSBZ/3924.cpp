#pragma comment(linker, "/STACK:1024000000,1024000000")
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <string>
#include <list>
#include <cstdlib>
#include <queue>
#include <stack>
#include <cmath>
#define ALL(a) a.begin(), a.end()
#define clr(a, x) memset(a, x, sizeof a)
#define fst first
#define snd second
#define pb push_back
#define ls (rt<<1)
#define rs (ls|1)
#define lson l, mid, ls
#define rson mid+1, r, rs
#define sqr(x) ((x)*(x))
using namespace std;
typedef long long LL;
typedef pair<int, int> pii;

const int maxn=120;
const LL oo=0x3f3f3f3f3f3f3f3f;

int n, m;
LL val[maxn], g[maxn][maxn];

int main()
{
    while(~scanf("%d%d", &n, &m))
    {
        clr(g, 0x3f);
        clr(val, 0);
        for(int i=1; i<=n; i++) g[i][i]=0;
        for(int i=0, u, v, w; i<n-1; i++)
        {
            scanf("%d%d%d", &u, &v, &w);
            g[u][v]=g[v][u]=w;
        }
        for(int k=1; k<=n; k++)
            for(int i=1; i<=n; i++)
                for(int j=1; j<=n; j++)
                    g[i][j]=min(g[i][j], g[i][k]+g[k][j]);
        while(m--)
        {
            int u, w;
            scanf("%d%d", &u, &w);
            val[u]+=w;
            LL ans=oo;
            for(int i=1; i<=n; i++)
            {
                LL tmp=0;
                for(int j=1; j<=n; j++)
                    tmp+=g[i][j]*val[j];
                ans=min(ans, tmp);
            }
            printf("%lld\n", ans);
        }
    }
    return 0;
}
/**
10 5
1 2 1
2 3 1
2 4 1
1 5 1
2 6 1
2 7 1
5 8 1
7 9 1
1 10 1
3 1
2 1
8 1
3 1
4 1
**/
