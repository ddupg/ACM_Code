#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long LL;
const int maxn=5100;
const int oo=0x3f3f3f3f;
int d[maxn][maxn], sum[maxn][maxn];
char s[2][maxn];
int n, m, st[2][30], en[2][30];

void init()
{
    n=strlen(s[0]);
    m=strlen(s[1]);
    memset(st, 0x3f, sizeof st);
    memset(en, -1, sizeof en);
    for(int i=0; i<n; i++)
        en[0][s[0][i]-'A']=i+1;
    for(int i=n-1; i>=0; i--)
        st[0][s[0][i]-'A']=i+1;
    for(int i=0; i<m; i++)
        en[1][s[1][i]-'A']=i+1;
    for(int i=m-1; i>=0; i--)
        st[1][s[1][i]-'A']=i+1;
}

int check(bool flag, int x, int y)
{
    if(!flag)
    {
        int c=s[flag][x-1]-'A';
        if(x==st[0][c] && y<st[1][c] && !(x==en[0][c] && y>=en[1][c]))return 1;
        if(x==en[0][c] && y>=en[1][c] && !(x==st[0][c] && y<st[1][c]))return -1;
        return 0;
    }
    if(flag)
    {
        int c=s[flag][y-1]-'A';
        if(x<st[0][c] && y==st[1][c] && !(x>=en[0][c] && y==en[1][c]))return 1;
        if(x>=en[0][c] && y==en[1][c] && !(x<st[0][c] && y==st[1][c]))return -1;
        return 0;
    }
}

LL dp()
{
    for(int i=0; i<=n; i++)
        for(int j=0; j<=m; j++)
            d[i][j]=oo;
    d[0][0]=0;
    sum[0][0]=0;
    for(int i=0; i<=n; i++)
        for(int j=0; j<=m; j++)
        {
            sum[i+1][j]=sum[i][j]+check(0, i+1, j);
            sum[i][j+1]=sum[i][j]+check(1, i, j+1);
            d[i+1][j]=min(d[i+1][j], d[i][j]+sum[i+1][j]);
            d[i][j+1]=min(d[i][j+1], d[i][j]+sum[i][j+1]);
        }
    return d[n][m];
}

int main()
{
    int T;
    scanf("%d", &T);
    while(T--)
    {
        scanf("%s%s", s[0], s[1]);
        init();
        printf("%lld\n", dp());
    }
    return 0;
}
