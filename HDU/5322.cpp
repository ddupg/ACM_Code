#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
using namespace std;
typedef long long LL;

const LL mod=998244353;
const int maxn=100000+100;

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
    const int G=3, gl=25;
    LL p, rp[50], irp[50];
    void init(LL _p)
    {
        p=_p;
        for(int i=0; i<gl; i++)
            rp[i]=powmod(G, (p-1)/(1<<i), p);
    }
    void FFT(LL a[], int n, LL wt[])
    {
        for(int i=0, j=0; i<n; i++)
        {
            if(j>i) swap(a[i], a[j]);
            int k=n;
            while(j & (k>>=1)) j&=~k;
            j |= k;
        }
        for(int m=1, b=1; m<n; m<<=1, b++)
            for(int k=0, w=1; k<m; ++k)
            {
                for(int i=k; i<n; i+=(m<<1))
                {
                    int v=a[i+m]*w%p;
                    if((a[i+m]=a[i]-v)<0)a[i+m]+=p;
                    if((a[i]+=v)>=p) a[i]-=p;
                }
                w=w*wt[b]%p;
            }
    }
    void IFFT(LL a[], int n)
    {
        for(int i=0; i<gl; i++)
            irp[i]=powmod(rp[i], n-1, p);
        FFT(a, n, irp);
        LL inv=powmod(n, p-2, p);
        for(int i=0; i<n; i++)
            a[i]=a[i]*inv%p;
    }
    void Mul(LL a[], LL b[], int n, LL c[])
    {
        FFT(a, n, rp);
        FFT(b, n, rp);
        for(int i=0; i<n; i++)c[i]=a[i]*b[i]%p;
        IFFT(c, n);
    }
} ntt;

LL d[maxn], a[maxn*3], b[maxn*3], x[maxn*3];
LL fac[maxn], inv[maxn];

void init()
{
    fac[0]=1, inv[0]=1;
    for(int i=1; i<maxn; i++)
    {
        fac[i]=fac[i-1]*i%mod;
        inv[i]=powmod(fac[i], mod-2, mod);
    }
}

void CDQ(int l, int r)
{
    if(l==r)return ;
    int mid=l+r>>1;
    CDQ(l, mid);
    int n=1;
    while(r-l+1>=n) n<<=1;
    for(int i=0; i<n; i++)
    {
        a[i]=(l+i<=mid ? d[l+i]*inv[l+i]%mod : 0);
        b[i]=(i+l<r ? 1LL*(1+i)*(1+i)%mod : 0);
    }
    ntt.Mul(a, b, n, x);
    for(int i=mid+1; i<=r; i++)
        d[i]=(d[i]+fac[i-1]*x[i-l-1]%mod)%mod;
    CDQ(mid+1, r);
}

int main()
{
    init();
    ntt.init(mod);
    d[0]=1;
    CDQ(0, 100000);
    for(int x; ~scanf("%d", &x); )
        printf("%I64d\n", d[x]);
    return 0;
}
