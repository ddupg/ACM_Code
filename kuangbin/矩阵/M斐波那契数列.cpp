#include <iostream>
#include <cstring>
#include <cstdio>
using namespace std;
typedef long long LL;
const int maxn=5;
const LL mod=1000000007;

struct Matrix
{
    LL m[maxn][maxn];
} init;

Matrix Mult(Matrix m1, Matrix m2)
{
    Matrix ans;
    for(int i=0; i<2; i++)
        for(int j=0; j<2; j++)
        {
            ans.m[i][j]=0;
            for(int k=0; k<2; k++)
                ans.m[i][j]=(ans.m[i][j]+m1.m[i][k]*m2.m[k][j])%(mod-1);
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
LL PowInt(LL x, LL b)
{
    LL ans=1;
    while(b)
    {
        if(b&1)
            ans=ans*x%mod;
        x=x*x%mod;
        b>>=1;
    }
    return ans;
}

int main()
{
    LL a, b, n;
    while(cin>>a>>b>>n)
    {
        if(n==0)
            cout<<a<<endl;
        else if(n==1)
            cout<<b<<endl;
        else
        {
            init.m[0][0]=init.m[0][1]=init.m[1][0]=1;
            init.m[1][1]=0;
            Matrix ans=Pow(init, n-1);
            cout<<PowInt(a, ans.m[0][1])*PowInt(b, ans.m[0][0])%mod<<endl;
        }
    }
    return 0;
}
