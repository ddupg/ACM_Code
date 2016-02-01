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
#include<cmath>
#define ALL(a) a.begin(), a.end()
#define clr(a, x) memset(a, x, sizeof a)
#define fst first
#define snd second
#define pb push_back
#define mp make_pair
#define rep(i,n) for(int i=0;i<(int)n;i++)
#define rep1(i,x,y) for(int i=x;i<=(int)y;i++)
using namespace std;
typedef long long LL;
typedef pair<int, int> pii;

const int maxn=200010;

int n, x[maxn], y[maxn], cx, cy, d[maxn][2], pre[maxn][2];
bool win[maxn];

int main()
{
    scanf("%d", &n);
    for(int i=0; i<n; i++)
    {
        scanf("%d%d", x+i, y+i);
        if(x[i]>y[i])
            cx++, win[i]=true;
    }
    if(cx>n/2)
    {
        puts("0");
        return 0;
    }
    clr(pre, -1);
    for(int i=1; i<n; i++)
    {
        if(d[i-1][0]>=d[i-1][1])
            d[i][0]=d[i-1][0], pre[i][0]=0;
        else d[i][0]=d[i-1][1], pre[i][0]=1;
        if(((win[i] ^ win[i-1]) && x[i]+x[i-1]>y[i]+y[i-1]) ||
                (!win[i] && !win[i-1]))
            d[i][1]=d[i-1][0]+1, pre[i][1]=0;

        if((n-d[i][1])/2<cx)
        {
            printf("%d\n", d[i][1]);
            for(int j=i, k=1; j; j--)
            {
                if(k)printf("%d %d\n", j, j+1);
                k=pre[j][k];
            }
            return 0;
        }
    }
    puts("-1");
    return 0;
}
