#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#define clr(a, x) memset(a, x, sizeof a)
using namespace std;
typedef long long LL;

const int maxn=300050;
const double PI=acos(-1.0);

struct Complex
{
    double a, b;
    Complex() {}
    Complex(double a, double b):a(a), b(b) {}
    Complex operator + (const Complex& e) { return Complex(a+e.a, b+e.b); }
    Complex operator - (const Complex& e) { return Complex(a-e.a, b-e.b); }
    Complex operator * (const Complex& e) { return Complex(a*e.a-b*e.b, a*e.b+b*e.a); }
} cd[maxn];

void change(Complex y[], int n)
{
    for(int i=0, j=0; i<n; i++)
    {
        if(j>i)swap(y[i], y[j]);
        int k=n;
        while(j & (k >>= 1))j &= ~k;
        j |= k;
    }
}

void FFT(Complex y[], int n, int on)
{
    change(y, n);
    for(int h=2; h<=n; h<<=1)
    {
        Complex wn(cos(-on*2*PI/h), sin(-on*2*PI/h));
        for(int j=0; j<n; j+=h)
        {
            Complex w(1, 0);
            for(int k=j; k<j+h/2; k++)
            {
                Complex u=y[k];
                Complex t=w*y[k+h/2];
                y[k]=u+t;
                y[k+h/2]=u-t;
                w=w*wn;
            }
        }
    }
    if(on==-1)
        for(int i=0; i<n; i++)
            y[i].a/=n;
}

int n, cnt[maxn/3], sum[maxn/3];

int main()
{
    int T;
    scanf("%d", &T);
    while(T--)
    {
        scanf("%d", &n);
        clr(cnt, 0);
        clr(sum, 0);
        int mx=0;
        for(int i=0, x; i<n; i++)
        {
            scanf("%d", &x);
            ++cnt[x];
            mx=max(mx, x);
        }
        int len=1;
        while(mx*2>=len)len<<=1;
        for(int i=0; i<=mx; i++) cd[i]=Complex(cnt[i], 0);
        for(int i=mx+1; i<=len; i++) cd[i]=Complex(0, 0);
        FFT(cd, len, 1);
        for(int i=0; i<len; i++)
            cd[i]=cd[i]*cd[i];
        FFT(cd, len, -1);
        for(int i=1; i<=mx; i++)
            sum[i]=sum[i-1]+cnt[i];
        LL tot=1LL*n*(n-1)*(n-2)/6, ans=tot;
        for(int i=2; i<=mx; i++)
        {
            LL x=(LL)(cd[i].a+0.5);
            if(!(i&1))x-=cnt[i>>1];
            ans-=(x>>1)*(n-sum[i-1]);
        }
        printf("%.7f\n", 1.0*ans/tot);
    }
    return 0;
}
