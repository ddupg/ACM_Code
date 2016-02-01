#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <algorithm>
using namespace std;
typedef long long LL;
typedef unsigned long long LLU;
const int N=10;
int MOD=1e9;

struct Matrix
{
    LL m[N][N];
} e, u;

void init()
{
    e.m[0][0]=e.m[1][1]=u.m[0][0]=u.m[0][1]=u.m[1][0]=1;
    e.m[0][1]=e.m[1][0]=u.m[1][1]=0;
}
int n, k, b;

Matrix Mult(Matrix a, Matrix b)
{
    Matrix ans;
    for(int i=0; i<2; i++)
        for(int j=0; j<2; j++)
        {
            ans.m[i][j]=0;
            for(int k=0; k<2; k++)
                ans.m[i][j]=(ans.m[i][j]+a.m[i][k]*b.m[k][j])%MOD;
        }
    return ans;
}

Matrix Pow(Matrix a, int b)
{
    Matrix ans;
    for(int i=0; i<2; i++)
        for(int j=0; j<2; j++)
            ans.m[i][j]=(i==j);
    while(b)
    {
        if(b&1)ans=Mult(ans, a);
        a=Mult(a, a);
        b>>=1;
    }
    return ans;
}

Matrix Add(Matrix a, Matrix b)
{
    for(int i=0; i<2; i++)
        for(int j=0; j<2; j++)
            a.m[i][j]=(a.m[i][j]+b.m[i][j])%MOD;
    return a;
}

Matrix BinarySum(Matrix a, int n)
{
    if(n==1)return a;
    return (n&1) ? Add(Pow(a, n), BinarySum(a, n-1)) : Mult(BinarySum(a, n>>1), Add(Pow(a, n>>1), e));
}

int main()
{
    init();
    while(~scanf("%d%d%d%d", &k, &b, &n, &MOD))
    {
        Matrix A=Pow(u, b);
        Matrix K=Pow(u, k);

        Matrix ans=Mult(A, Add(e, BinarySum(K, n-1)));
        printf("%d\n", ans.m[0][1]);
    }
    return 0;
}
