#include <cstdio>
#define ls (rt<<1)
#define rs (ls|1)
#define lson l, mid, ls
#define rson mid+1, r, rs
using namespace std;

const int maxn=100000+100;

bool ispri[1000000+100];
int sum[maxn<<2], cov[maxn<<2], x[maxn<<2];

void init()
{
    for(int i=2; i<1e6; i++)
        ispri[i]=true;
    for(int i=2; i*i<=1e6; i++)
        if(ispri[i])
            for(int j=i*i; j<=1e6; j+=i)
                ispri[j]=false;
}

void pushup(int rt)
{
    sum[rt]=sum[ls]+sum[rs];
}

void pushdown(int l, int r, int rt)
{
    if(~cov[rt])
    {
        cov[ls]=cov[rs]=cov[rt];
        x[ls]=x[rs]=cov[rt];
        int mid=l+r>>1;
        sum[ls]=(mid-l+1)*ispri[cov[rt]];
        sum[rs]=(r-mid)*ispri[cov[rt]];
        cov[rt]=-1;
    }
}

void build(int l, int r, int rt)
{
    cov[rt]=-1;
    if(l==r)
    {
        scanf("%d", x+rt);
        sum[rt]=ispri[x[rt]];
        return ;
    }
    int mid=l+r>>1;
    build(lson);
    build(rson);
    pushup(rt);
}

void change(int p, int v, int l, int r, int rt)
{
    if(l==r)
    {
        x[rt]+=v;
        sum[rt]=ispri[x[rt]];
        return ;
    }
    pushdown(l, r, rt);
    int mid=l+r>>1;
    if(p<=mid)change(p, v, lson);
    else change(p, v, rson);
    pushup(rt);
}

void replace(int L, int R, int v, int l, int r, int rt)
{
    if(L<=l && R>=r)
    {
        cov[rt]=v;
        sum[rt]=(r-l+1)*ispri[v];
        x[rt]=v;
        return ;
    }
    pushdown(l, r, rt);
    int mid=l+r>>1;
    if(L<=mid)replace(L, R, v, lson);
    if(R> mid)replace(L, R, v, rson);
    pushup(rt);
}

int query(int L, int R, int l, int r, int rt)
{
    if(L<=l && R>=r)
        return sum[rt];
    pushdown(l, r, rt);
    int mid=l+r>>1, ans=0;
    if(L<=mid)ans+=query(L, R, lson);
    if(R>mid) ans+=query(L, R, rson);
    return ans;
}

int main()
{
    init();
    int T, n, m;
    scanf("%d", &T);
    while(T--)
    {
        scanf("%d%d", &n, &m);
        build(1, n, 1);
        char op[10];
        int x, y, z;
        while(m--)
        {
            scanf("%s", op);
            if(op[0]=='A')
            {
                scanf("%d%d", &x, &y);
                change(y, x, 1, n, 1);
            }
            else if(op[0]=='R')
            {
                scanf("%d%d%d", &z, &x, &y);
                replace(x, y, z, 1, n, 1);
            }
            else
            {
                scanf("%d%d", &x, &y);
                printf("%d\n", query(x, y, 1, n, 1));
            }
        }
    }
    return 0;
}
