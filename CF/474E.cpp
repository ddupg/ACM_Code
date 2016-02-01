#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define clr(a, x) memset(a, x, sizeof a)
#define fst first
#define snd second
#define ls (rt<<1)
#define rs (ls|1)
#define lson l, mid, ls
#define rson mid+1, r, rs
using namespace std;
typedef long long LL;
typedef pair<int, int> pii;

const int maxn=100000+100;

int n, lim, m, d[maxn], pre[maxn];
LL  a[maxn], b[maxn];
int mx[maxn<<2], pos[maxn<<2];

void pushup(int rt)
{
    if(mx[ls]>=mx[rs])
        mx[rt]=mx[ls], pos[rt]=pos[ls];
    else mx[rt]=mx[rs], pos[rt]=pos[rs];
}

void insert(int x, int p, int v, int l, int r, int rt)
{
    if(l==r)
    {
        if(v>mx[rt])
        {
            mx[rt]=v;
            pos[rt]=p;
        }
        return ;
    }
    int mid=l+r>>1;
    if(x<=mid)insert(x, p, v, lson);
    else insert(x, p, v, rson);
    pushup(rt);
}

pii query(int L, int R, int l, int r, int rt)
{
    if(L<=l && R>=r)return pii(mx[rt], pos[rt]);
    int mid=l+r>>1;
    pii ans(0, 0);
    if(L<=mid) ans=max(ans, query(L, R, lson));
    if(R>mid) ans=max(ans, query(L, R, rson));
    return ans;
}

void print(int x)
{
    if(pre[x])
    {
        print(pre[x]);
        putchar(' ');
    }
    printf("%d", x);
}

int main()
{
    scanf("%d%d", &m, &lim);
    for(int i=1; i<=m; i++)
    {
        scanf("%I64d", a+i);
        b[i]=a[i];
    }
    sort(b+1, b+1+m);
    n=unique(b+1, b+1+m)-b-1;
    int len=0, ans;
    for(int i=1; i<=m; i++)
    {
        int L=upper_bound(b+1, b+1+n, a[i]-lim)-b;
        int R=lower_bound(b+1, b+1+n, a[i]+lim)-b;
        d[i]=-1;
        if(L>1)
        {
            pii t=query(1, L-1, 1, n, 1);
            if(t.fst+1>d[i])d[i]=t.fst+1, pre[i]=t.snd;
        }
        if(R<=n)
        {
            pii t=query(R, n, 1, n, 1);
            if(t.fst+1>d[i])d[i]=t.fst+1, pre[i]=t.snd;
        }
        insert(lower_bound(b+1, b+1+n, a[i])-b, i, d[i], 1, n, 1);
        if(d[i]>len)len=d[ans=i];
    }
    printf("%d\n", len);
    print(ans);
    puts("");
    return 0;
}
