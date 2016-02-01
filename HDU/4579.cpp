#include <iostream>
#include <cstdio>
#include <cstring>
#define clr(a, x) memset(a, x, sizeof a)
using namespace std;

const int maxn=50500;
const int base=6;

int n, m;
double a[maxn][base<<1], x[maxn];
double C[maxn][base<<1];

void Gauss()
{
    int i, j, k, r;
    for(i=0; i<n; i++)
        for(k=1; k<=m && i+k<n; k++)
        {
            double f=a[i+k][base-k]/a[i][base];
            for(j=0; j<=m; j++)
                a[i+k][base-k+j]-=f*a[i][base+j];
            x[i+k]-=f*x[i];
        }
    for(i=n-1; i>=0; i--)
    {
        for(j=1; j<=m && i+j<n; j++)
            x[i]-=x[i+j]*a[i][base+j];
        x[i]/=a[i][base];
    }
}

int main()
{
    while(~scanf("%d%d", &n, &m) && n+m)
    {
        clr(a, 0);
        clr(x, 0);
        clr(C, 0);
        for(int i=0; i<n; i++)
            for(int j=1; j<=m; j++)
                scanf("%lf", &C[i][j]);
        for(int i=0; i<n-1; i++)
        {
            a[i][base]=1;
            double s=0, t=1;
            for(int j=1; j<=m; j++) t+=C[i][j];
            for(int j=1; j<=m; j++)
            {
                if(i>=j)s+=(a[i][base-j]=-0.3*C[i][j]/t);
                if(i+j<n)s+=(a[i][base+j]=-0.7*C[i][j]/t);
            }
            a[i][base]=-s;
            x[i]=1;
        }
        a[n-1][base]=1, x[n-1]=0;
        Gauss();
        printf("%.2f\n", x[0]);
    }
    return 0;
}
