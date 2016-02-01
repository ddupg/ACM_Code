#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long LL;
const int maxn=10000+10;
const LL oo=0x3f3f3f3f3f3f3f3f;

template<class T>
inline void scan_d(T &ret)
{
    char c;
    int flag = 0;
    ret=0;
    while(((c=getchar())<'0'||c>'9')&&c!='-');
    if(c == '-')
    {
        flag = 1;
        c = getchar();
    }
    while(c>='0'&&c<='9') ret=ret*10+(c-'0'),c=getchar();
    if(flag) ret = -ret;
}

int n, pos[maxn], t[maxn];
LL d[maxn][maxn][2];
struct Node
{
    int p, t;
    bool operator < (const Node& a)const
    {
        return p<a.p;
    }
} nd[maxn];

void dp()
{
    for(int i=0; i<n; i++)
        d[i][i][0]=d[i][i][1]=0;
    for(int i=n-1; i>=0; i--)
        for(int j=i+1; j<n; j++)
        {
            d[i][j][0]=d[i][j][1]=oo;
            if(d[i+1][j][0]+nd[i+1].p-nd[i].p<nd[i].t)
                d[i][j][0]=min(d[i][j][0], d[i+1][j][0]+nd[i+1].p-nd[i].p);
            if(d[i+1][j][1]+nd[j].p-nd[i].p<nd[i].t)
                d[i][j][0]=min(d[i][j][0], d[i+1][j][1]+nd[j].p-nd[i].p);
            if(d[i][j-1][0]+nd[j].p-nd[i].p<nd[j].t)
                d[i][j][1]=min(d[i][j][1], d[i][j-1][0]+nd[j].p-nd[i].p);
            if(d[i][j-1][1]+nd[j].p-nd[j-1].p<nd[j].t)
                d[i][j][1]=min(d[i][j][1], d[i][j-1][1]+nd[j].p-nd[j-1].p);
        }
    LL ans=min(d[0][n-1][0], d[0][n-1][1]);
    if(ans<oo)
        printf("%lld\n", ans);
    else puts("No solution");
}

int main()
{
    while(~scanf("%d", &n))
    {
        for(int i=0; i<n; i++)
        {
            scan_d(nd[i].p);
            scan_d(nd[i].t);
        }
        sort(nd, nd+n);
        dp();
    }
    return 0;
}
