#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <cmath>
#define clr(a, x) memset(a, x, sizeof a)
#define ls (rt<<1)
#define rs (ls|1)
#define lson l, mid, ls
#define rson mid+1, r, rs
using namespace std;
typedef long long LL;

const int maxn=100000+100;
const LL mod=880803841;

int lazy[maxn<<2];
int sum[maxn<<2];

void pushup(int rt)
{
    sum[rt]=sum[ls]+sum[rs];
}

void pushdown(int l, int r, int rt)
{
    if(!lazy[rt]) return ;
    int mid=l+r>>1;
    lazy[ls]^=1, lazy[rs]^=1;
    sum[ls]=mid-l+1-sum[ls];
    sum[rs]=r-mid-sum[rs];
    lazy[rt]=0;
}

void build(int l, int r, int rt)
{
    lazy[rt]=0;
    if(l==r)
    {
        sum[rt]=1;
        return ;
    }
    int mid=l+r>>1;
    build(lson);
    build(rson);
    pushup(rt);
}

void update(int L, int R, int l, int r, int rt)
{
    if(L<=l && R>=r)
    {
        lazy[rt]^=1;
        sum[rt]=r-l+1-sum[rt];
        return ;
    }
    pushdown(l, r, rt);
    int mid=l+r>>1;
    if(L<=mid) update(L, R, lson);
    if(R>mid) update(L, R, rson);
    pushup(rt);
}

LL powmod(LL x, LL b, LL mod)
{
    LL ans=1;
    for(; b; b>>=1)
    {
        if(b&1)ans=ans*x%mod;
        x=x*x%mod;
    }
    return ans;
}

struct NTT
{
    const int r = 26, gl = 25;
    LL p, rp[50], irp[50];
    void init(LL _p = 880803841)
    {
        p = _p;
        for(int i = 0; i < gl; i++) rp[i] = powmod(r, (p-1)/(1<<i), p);
    }
    void FFT(LL a[], int n, LL wt[])
    {
        for(int i = 0, j = 0; i < n; i++)
        {
            if(j > i) swap(a[i], a[j]);
            int k = n;
            while(j & (k >>= 1)) j &= ~k;
            j |= k;
        }
        for(int m = 1, b = 1; m < n; m<<=1, b++)
            for(int k = 0, w = 1; k < m; ++k)
            {
                for(int i = k; i < n; i += m<<1)
                {
                    int v = a[i+m] * w % p;
                    if((a[i+m] = a[i] - v) < 0) a[i+m] += p;
                    if((a[i] += v) >= p) a[i] -= p;
                }
                w = w * wt[b] % p;
            }
    }
    void IFFT(LL a[], int n)
    {
        for(int i = 0; i < gl; i++) irp[i] = powmod(rp[i], n-1, p);
        FFT(a, n, irp);
        LL inv = powmod(n, p-2, p);
        for(int i = 0; i < n; i++) a[i] = a[i] * inv % p;
    }
    void Mul(LL a[], LL b[], LL n, LL c[])
    {
        FFT(a, n, rp);
        FFT(b, n, rp);
        for(int i = 0; i < n; i++) c[i] = a[i] * b[i] % p;
        IFFT(c, n);
    }
} ntt;

LL S[maxn*3], a[maxn*3], b[maxn*3];

int main()
{
    int T, M, N, D;
    scanf("%d", &T);
    while(T--)
    {
        scanf("%d%d%d", &M, &N, &D);
        clr(a, 0), clr(b, 0);
        int n=1;
        while((M<<1)>=n)n<<=1;

        a[0]=1, b[0]=0;
        LL base=1;
        for(int i=1; i<=M; i++)
        {
            base=base*i%mod;
            a[i]=((i&1)?(mod-1):1)*powmod(base, mod-2, mod)%mod;
            b[i]=powmod(base, mod-2, mod)*powmod(i, M, mod)%mod;
        }

        ntt.init();
        ntt.Mul(a, b, n, S);

        build(1, N, 1);
        while(D--)
        {
            int l, r;
            scanf("%d%d", &l, &r);
            update(l, r, 1, N, 1);
            printf("%d\n", (int)S[sum[1]]);
        }
    }
    return 0;
}
