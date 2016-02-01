#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
#define clr(a, x) memset(a, x, sizeof a)
using namespace std;

const int maxn=600000;
const long double PI = acos(0.0) * 2.0;

struct Complex
{
    long double a, b;
    Complex(long double a=0, long double b=0):a(a), b(b) {}
    Complex operator + (const Complex& e) { return Complex(a+e.a, b+e.b); }
    Complex operator - (const Complex& e) { return Complex(a-e.a, b-e.b); }
    Complex operator * (const Complex& e) { return Complex(a*e.a-b*e.b, a*e.b+b*e.a); }
} a[4][maxn], ans[maxn];

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

bool vis[maxn];

void getCoPri()
{
    for(int i=2; i*i<=50000; i++)if(!vis[i])
        for(int j=i*i; j<=50000; j+=i)
            vis[j]=true;
}

int main()
{
    getCoPri();
    int L, R, k;
    while(scanf("%d%d%d", &L, &R, &k) && L+R+k)
    {
        int n=2;
        while((R<<2)>=n)n<<=1;
        for(int i=0; i<=n; i++)
            for(int j=0; j<4; j++)
                a[j][i]=Complex(i<=R?vis[i]:0, 0);
        while(k--)
        {
            int x;
            char c;
            scanf("%d%c", &x, &c);
            if(c=='S') a[0][x].a=0;
            if(c=='H') a[1][x].a=0;
            if(c=='C') a[2][x].a=0;
            if(c=='D') a[3][x].a=0;
        }
        for(int i=0; i<4; i++)
            FFT(a[i], n, 1);
        for(int i=0; i<n; i++)
            ans[i]=a[0][i]*a[1][i]*a[2][i]*a[3][i];
        FFT(ans, n, -1);
        for(int i=L; i<=R; i++)
            printf("%lld\n", (long long)(0.5+ans[i].a));
        puts("");
    }
    return 0;
}
