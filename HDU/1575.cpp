#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <cmath>
using namespace std;
typedef long long LL;
typedef unsigned long long LLU;
const int N=15;
const int MOD=9973;
int n;
struct Mat
{
    int m[N][N];
};

Mat Mul(Mat a, Mat b)
{
    Mat res;
    memset(res.m, 0, sizeof(res.m));
    for(int i=0; i<n; i++)
        for(int j=0; j<n; j++)
            for(int k=0; k<n; k++)
                res.m[i][j]=(res.m[i][j]+a.m[i][k]*b.m[k][j])%MOD;
    return res;
}

Mat power(Mat a, int n)
{
    if(n==1)
        return a;
    Mat res=power(a, n/2);
    res=Mul(res, res);
    if(n&1)
        return Mul(res, a);
    return res;
}

int main()
{
    int t;
    scanf("%d", &t);
    while(t--)
    {
        int k;
        scanf("%d%d", &n, &k);
        Mat a;
        memset(a.m, 0, sizeof(a.m));
        for(int i=0; i<n; i++)
            for(int j=0; j<n; j++)
                scanf("%d", &a.m[i][j]);
        a=power(a, k);
        int ans=0;
        for(int i=0; i<n; i++)
            ans=(ans+a.m[i][i])%MOD;
        printf("%d\n", ans);
    }
    return 0;
}
