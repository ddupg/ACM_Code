#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstring>
using namespace std;

const int maxn=80100*3;

struct Complex
{
    double a, b;
    Complex(double a=0, double b=0):a(a), b(b) {}
    Complex operator + (const Complex& e) { return Complex(a+e.a, b+e.b); }
    Complex operator - (const Complex& e) { return Complex(a-e.a, b-e.b); }
    Complex operator * (const Complex& e) { return Complex(a*e.a-b*e.b, a*e.b+b*e.a); }
};

void change(Complex y[], int n)
{
    for(int i=0, j=0; i<n; i++)
    {
        if(j>i)swap(y[i], y[j]);
        int k=n;
        while(j & (k>>=1)) j &= ~k;
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

Complex a[maxn];

int cnt[maxn], pre[maxn];

void init()
{
    for(int i=2; i<maxn; i++)if(!pre[i])
        for(int j=i; j<maxn; j+=i)
            pre[j]=i;
    for(int i=2; i<maxn; i++)
        for(int t=i; t>1; t/=pre[t])
            cnt[i]++;
}

int main()
{
    int x;
    while(~scanf("%d", &x))
    {
        int n=1;
        while(n<=(x*3))n<<=1;
        for(int i=0; i<n; i++)
            a[i]=Complex(0, 0);

    }
    return 0;
}
