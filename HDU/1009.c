#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

double J[1111], F[1111], w[1111];
double M;
int n;

void sort_w()
{
    int i, j;
    for(i=0; i<n; i++)
        for(j=i+1; j<n; j++)
            if(w[i]<w[j])
            {
                double t=w[i];
                w[i]=w[j];
                w[j]=t;

                t=J[i];
                J[i]=J[j];
                J[j]=t;

                t=F[i];
                F[i]=F[j];
                F[j]=t;
            }
}

void solve()
{
    double ans=0;
    int i;
    for(i=0; i<n; i++)
    {
        if(M>=F[i])
        {
            M-=F[i];
            ans+=J[i];
        }
        else
        {
            ans+=M/F[i]*J[i];
            M=0;
            break;
        }
    }
    printf("%.3lf\n", ans);
}

int main()
{
    while(scanf("%lf%d", &M, &n)!=EOF && (M!=-1 && n!=-1))
    {
        int i;
        for(i=0; i<n; i++)
        {
            scanf("%lf%lf", &J[i], &F[i]);
            w[i]=J[i]/F[i];
        }
        sort_w();
        solve();
    }
    return 0;
}
