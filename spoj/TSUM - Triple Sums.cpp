#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#define clr(a, x) memset(a, x, sizeof a)
using namespace std;
typedef long long LL;
typedef pair<int, int> pii;

const int maxn=400000;
const double PI=acos(-1.0);

struct Complex
{
    double a, b;
    Complex(double a=0, double b=0):a(a), b(b){}
    Complex operator + (const Complex& e){ return Complex(a+e.a, b+e.b); }
    Complex operator - (const Complex& e){ return Complex(a-e.a, b-e.b); }
    Complex operator * (const Complex& e){ return Complex(a*e.a-b*e.b, a*e.b+b*e.a); }
};

void change(Complex y[], int n)
{
    for(int i=0, j=0; i<n; i++)
    {
        if(j>i)swap(y[i], y[j]);
        int k=n;
        while(j & (k>>=1)) j&=~k;
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
                Complex u=y[k], t=w*y[k+h/2];
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

int cnt[3][maxn/3];
Complex f[2][maxn];

int main()
{
    int n;
    while(~scanf("%d", &n))
    {
        clr(cnt, 0);
        int mx=0;
        for(int i=0, x; i<n; i++)
        {
            scanf("%d", &x);
            x+=20000;
            mx=max(mx, x*3);
            for(int j=0; j<3; j++)
                ++cnt[j][x*(j+1)];
        }
        int len=1;
        while(mx>=len)len<<=1;
        for(int i=0; i<=2*mx; i++)
        {
            f[0][i]=Complex(cnt[0][i], 0);
            f[1][i]=Complex(cnt[1][i], 0);
        }
        for(int i=2*mx+1; i<len; i++)
            f[0][i]=f[1][i]=Complex(0, 0);

        FFT(f[0], len, 1);
        FFT(f[1], len, 1);

        for(int i=0; i<len; i++)
        {
            f[1][i]=f[1][i]*f[0][i];
            f[0][i]=f[0][i]*f[0][i]*f[0][i];
        }
        FFT(f[0], len, -1);
        FFT(f[1], len, -1);
        for(int i=0; i<len; i++)
        {
            int x=(((int)(f[0][i].a+0.5))-3*((int)(f[1][i].a+0.5))+2*cnt[2][i])/6;
            if(x)printf("%d : %d\n", i-60000, x);
        }
    }
    return 0;
}
