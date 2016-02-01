#include <iostream>
#include <cstdio>
#include <cmath>
#include <vector>
using namespace std;

const int maxn=3000000+100;
const double PI=acos(-1.0);

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

int n, m, has[maxn];
Complex a[maxn];
vector<int> ans;

int main()
{
    scanf("%d%d", &n, &m);
    has[0]=1;
    for(int i=0; i<n; i++)
    {
        int x;
        scanf("%d", &x);
        has[x]=1;
    }
    for(int i=1; i<=m; i++)if(has[i])
            for(int j=i+i; j<=m; j+=i)
                if(!has[j])
                {
                    puts("NO");
                    return 0;
                }
    int len=1;
    while((m<<1)>=len) len<<=1;
    for(int i=0; i<=m; i++)
        if(has[i])a[i].a=1;
    FFT(a, len, 1);
    for(int i=0; i<len; i++)
        a[i]=a[i]*a[i];
    FFT(a, len, -1);
    for(int i=1; i<=m; i++)
    {
        int t=(int)(a[i].a+0.5);
        if(has[i] && t<=2)
            ans.push_back(i);
        else if(!has[i] && t)
        {
            puts("NO");
            return 0;
        }
    }
    printf("YES\n%d\n", ans.size());
    for(int i=0; i<ans.size(); i++)
    {
        if(i)putchar(' ');
        printf("%d", ans[i]);
    }
    return 0;
}
