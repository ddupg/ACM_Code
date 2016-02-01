#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cstring>
using namespace std;
typedef long long LL;
const int maxn=110;
const int MOD=1e9+7;
LL d[maxn][maxn], C[maxn][maxn];
int n, a[maxn];

void init()
{
    for(int i=0; i<=100; i++)
        C[i][0]=1;
    for(int i=1; i<=100; i++)
        for(int j=1; j<=i; j++)
            C[i][j]=(C[i-1][j-1]+C[i-1][j])%MOD;
}

LL dp(int l, int r)
{
    if(l>r)return 0;
    if(d[l][r]!=-1)return d[l][r];
    if(l==r)return d[l][r]=1;
    LL res=(dp(l+1, r)+dp(l, r-1))%MOD;
    for(int k=l+1; k<r; k++)
        if(a[k-1]==a[k+1])
            res=(res+dp(l, k-1)*dp(k+1, r)%MOD*C[r-l][k-l]%MOD)%MOD;
    return d[l][r]=res;
}

int main()
{
    init();
    while(cin>>n)
    {
        for(int i=1; i<=n; i++)
            cin>>a[i];
        a[0]=a[n+1]=-1;
        memset(d, -1, sizeof(d));
        cout<<dp(1, n)<<endl;
    }
    return 0;
}
