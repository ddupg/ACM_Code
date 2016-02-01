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
#define ALL(a) a.begin(), a.end()
#define clr(a, x) memset(a, x, sizeof a)
#define fst first
#define snd second
#define pb push_back
using namespace std;
typedef long long LL;
typedef pair<int, int> pii;

const int maxn=450;

LL d[200000+100];
int pre[200000+100][55];
pii nd[maxn];
map<LL, int> mp;

int main()
{
    for(int i=0; i<=50; i++)
        mp[1LL<<i]=i;
    int T;
    scanf("%d", &T);
    while(T--)
    {
        int n, q;
        scanf("%d%d", &n, &q);
        clr(d, 0);
        d[0]=1;
        for(int i=1; i<=n; i++)
        {
            scanf("%d%d", &nd[i].fst, &nd[i].snd);
            for(int j=200000; j>=nd[i].snd; j--)
            {
                LL t=d[j];
                d[j] |= (d[j-nd[i].snd]<<nd[i].fst);
                for(LL dif=d[j]^t; dif && (t=(dif&-dif)); dif-=t)
                    if(mp[t]<=50)
                        pre[j][mp[t]]=i;
            }
        }
        while(q--)
        {
            int x, y;
            scanf("%d%d", &x, &y);
            if(!(d[y]&(1LL<<x)))
                puts("No solution!");
            else
            {
                bool first=true;
                while(x)
                {
                    int i=pre[y][x];
                    x-=nd[i].fst;
                    y-=nd[i].snd;
                    if(!first)putchar(' ');
                    first=false;
                    printf("%d", i);
                    if(!x && !y)break;
                }
                puts("");
            }
        }
    }
    return 0;
}
