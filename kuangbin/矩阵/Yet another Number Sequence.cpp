#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long LL;
const int maxn=3;

int mod;

struct Matrix
{
    int m[maxn][maxn];
} init;
Matrix Mult(Matrix m1, Matrix m2)
{
    Matrix ans;
    for(int i=0; i<2; i++)
        for(int j=0; j<2; j++)
        {
            ans.m[i][j]=0;
            for(int k=0; k<2; k++)
                ans.m[i][j]=(ans.m[i][j]+m1.m[i][k]*m2.m[k][j])%mod;
        }
    return ans;
}
Matrix Pow(Matrix m1, int b)
{
    Matrix ans;
    for(int i=0; i<2; i++)
        for(int j=0; j<2; j++)
            ans.m[i][j]=(i==j);
    while(b)
    {
        if(b&1)
            ans=Mult(ans, m1);
        m1=Mult(m1, m1);
        b>>=1;
    }
    return ans;
}

int main()
{
    int T;
    scanf("%d", &T);
    while(T--)
    {
        int a, b, n, m;
        scanf("%d%d%d%d", &a, &b, &n, &m);
        mod=1;
        while(m--)
            mod*=10;
        init.m[0][0]=init.m[0][1]=init.m[1][0]=1, init.m[1][1]=0;
        if(n==0)
            printf("%d\n", a);
        else
        {
            Matrix ans=Pow(init, n-1);
            printf("%d\n", (ans.m[0][0]*b+ans.m[0][1]*a)%mod);
        }
    }
    return 0;
}
