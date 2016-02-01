#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
using namespace std;
typedef long long LL;
const int maxn=5;
const LL MOD=1000000007;
struct Matrix
{
    LL m[maxn][maxn];
} init;
Matrix Mult(Matrix m1,Matrix m2)
{
    Matrix ans;
    for(int i=0; i<2; i++)
        for(int j=0; j<2; j++)
        {
            ans.m[i][j]=0;
            for(int k=0; k<2; k++)
                ans.m[i][j]=(ans.m[i][j]+m1.m[i][k]*m2.m[k][j])%MOD;
        }
    return ans;
}
Matrix Pow(Matrix m1,int b)
{
    Matrix ans;
    for(int i=0; i<2; i++)
        for(int j=0; j<2; j++)
            ans.m[i][j]=(i==j);
    while(b)
    {
        if(b&1)
            ans=Mult(ans,m1);
        m1=Mult(m1,m1);
        b>>=1;
    }
    return ans;
}

int main()
{
    init.m[0][0]=1, init.m[0][1]=-1, init.m[1][0]=1, init.m[1][1]=0;
    LL x, y, n;
    cin>>x>>y;
    cin>>n;
    if(n==1)
        cout<<(x+MOD)%MOD<<endl;
    else if(n==2)
        cout<<(y+MOD)%MOD<<endl;
    else
    {
        Matrix ans=Pow(init, n-2);
        LL res=(y*ans.m[0][0]+x*ans.m[0][1])%MOD;
        if(res<0)res+=MOD;
        cout<<res<<endl;
    }
    return 0;
}
