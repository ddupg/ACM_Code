#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long LL;
const int maxn=4;

LL n, mod;

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
    while(cin>>n>>mod)
    {
        if(n<=2)
        {
            cout<<n%mod<<endl;
            continue ;
        }
        init.m[0][0]=4, init.m[1][0]=0, init.m[1][1]=1;
        if(n&1)init.m[0][1]=1;
        else init.m[0][1]=2;
        Matrix ans=Pow(init, (n>>1));
        if(n&1)
            cout<<(ans.m[0][0]+ans.m[0][1])%mod<<endl;
        else cout<<(ans.m[0][1])%mod<<endl;
    }
    return 0;
}
