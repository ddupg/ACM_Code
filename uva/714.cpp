#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <list>
#include <queue>
#include <stack>
#include <cmath>
#define clr(a, x) memset(a, x, sizeof a)
#define ALL(a) a.begin(), a.end()
#define fst first
#define snd second
#define ls (rt<<1)
#define rs (ls|1)
#define lson l, mid, ls
#define rson mid+1, r, rs
using namespace std;
typedef long long LL;
const int maxn=550;

int val[maxn], n, m, bel[maxn];

bool judge(LL lim)
{
    int i, j;
    for(j=m-1, i=n-1; j>=0; j--)
    {
        LL tmp=lim;
        for(; i>=j && tmp>=val[i]; i--)
        {
            tmp-=val[i];
            bel[i]=j;
        }
    }
    return i<0;
}

int main()
{
    int T;
    scanf("%d", &T);
    while(T--)
    {
        scanf("%d%d", &n, &m);
        LL sum=0;
        for(int i=0; i<n; i++)
        {
            scanf("%d", val+i);
            sum+=val[i];
        }
        LL L=0, R=sum;
        while(L<R)
        {
            LL mid=L+R>>1;
            if(judge(mid))
                R=mid;
            else L=mid+1;
        }
        judge(L);
        printf("%d", val[0]);
        for(int i=1; i<n; i++)
        {
            if(bel[i]!=bel[i-1])
                printf(" /");
            printf(" %d", val[i]);
        }
        puts("");
    }
    return 0;
}
