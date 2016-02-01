#include <cstdio>
#include <iostream>
#include <cstring>
#include <cmath>
using namespace std;
const double eps=1e-5;

int main()
{
    double m[15][35];
    int e[15][35];
    for(int i=0; i<=9; i++)
        for(int j=1; j<=30; j++)
        {
            double a=1.0-pow(2, -(i+1));
            int b=(1<<j)-1;
            double tmp=log10(a)+b*log10(2.0);
            m[i][j]=pow(10, tmp-floor(tmp));
            e[i][j]=floor(tmp);
        }

    double a;
    int b;
    char s[30];
    while(scanf("%s", s))
    {
        if(!strcmp(s, "0e0"))return 0;
        for(int i=0; s[i]; i++)
            if(s[i]=='e')s[i]=' ';
        sscanf(s, "%lf %d", &a, &b);
        for(int i=0; i<=9; i++)
            for(int j=1; j<=30; j++)
                if(fabs(a-m[i][j])<eps && b==e[i][j])
                    printf("%d %d\n", i, j);
    }
    return 0;
}
