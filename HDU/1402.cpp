#include <iostream>
#include <complex>
#include <cmath>
#include <vector>
#include <cstdio>
#include <algorithm>
#include <cstdlib>
#include <cstring>
#include <cmath>
using namespace std;
const long double PI=acos(-1.0);
typedef complex<double> CD;

void change(CD y[], int n)
{
    for(int i=0, j=0; i<n; i++)
    {
        if(j>i)swap(y[i], y[j]);
        int k=n;
        while(j & (k>>=1)) j &= ~k;
        j |= k;
    }
}

void FFT(CD y[], int n, int on)
{
    change(y, n);
    for(int h=2; h<=n; h<<=1)
    {
        CD wn(cos(-on*2*PI/h), sin(-on*2*PI/h));
        for(int j=0; j<n; j+=h)
        {
            CD w(1, 0);
            for(int k=j; k<j+h/2; k++)
            {
                CD u=y[k];
                CD t=w*y[k+h/2];
                y[k]=u+t;
                y[k+h/2]=u-t;
                w=w*wn;
            }
        }
    }
    if(on==-1)
        for(int i=0; i<n; i++)
            y[i].real(y[i].real()/n);
}

const int maxn=200020;

char s1[maxn], s2[maxn];
CD a[maxn], b[maxn];
int ans[maxn];

int main()
{
    while(~scanf("%s%s", s1, s2))
    {
        int len1=strlen(s1), len2=strlen(s2);
        int n=1;
        while(len1+len2>=n)n<<=1;

        for(int i=0; i<n; i++)
            a[i]=CD(i<len1?s1[len1-1-i]-'0':0, 0);
        for(int i=0; i<n; i++)
            b[i]=CD(i<len2?s2[len2-1-i]-'0':0, 0);

        FFT(a, n, 1);
        FFT(b, n, 1);
        for(int i=0; i<n; i++)
            a[i]=a[i]*b[i];
        FFT(a, n, -1);
        for(int i=0; i<n; i++)
            ans[i]=(int)(a[i].real()+0.5);
        int p=0;
        for(int i=0; i<n; i++)
        {
            ans[i+1]+=ans[i]/10;
            ans[i]%=10;
            if(ans[i]>0)p=i;
        }
        for(int i=p; i>=0; i--)
            putchar(ans[i]+'0');
        puts("");
    }
    return 0;
}
