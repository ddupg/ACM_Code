#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long LL;
typedef unsigned long long LLU;

const int N=12;
int MOD, n, m;

struct Matrix
{
    int m[N][N];
};

Matrix Mult(Matrix a, Matrix b)
{
    Matrix ans;
    for(int i=0; i<n; i++)
        for(int j=0; j<n; j++)
        {
            ans.m[i][j]=0;
            for(int k=0; k<n; k++)
                ans.m[i][j]=(ans.m[i][j]+a.m[i][k]*b.m[k][j])%MOD;
        }
    return ans;
}

Matrix Pow(Matrix a, int b)
{
    Matrix ans;
    for(int i=0; i<n; i++)
        for(int j=0; j<n; j++)
            ans.m[i][j]=(i==j);
    while(b)
    {
        if(b&1)ans=Mult(ans, a);
        a=Mult(a, a);
        b>>=1;
    }
    return ans;
}

int main()
{
    int k;
    while(~scanf("%d%d", &k, &MOD))
    {
        if(k<10)
        {
            printf("%d\n", k);
        }
        Matrix a;
        n=10, m=1;
        for(int i=0; i<n; i++)
            for(int j=0; j<n; j++)
                a.m[i][j]=(i==j-1);
        for(int i=0; i<n; i++)
            scanf("%d", &a.m[9][9-i]);

        Matrix t=Pow(a, k-9);

        int ans=0;
        for(int i=0; i<10; i++)
            ans=(ans+t.m[9][i]*i)%MOD;
        printf("%d\n", ans);
    }
    return 0;
}
