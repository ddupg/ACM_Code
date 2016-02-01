#include <cstdio>
#include <cstring>
using namespace std;

int d[15][3][15], n, num[15], cnt;

int dp(int i, int s, int v, bool e)
{
    if(i==-1)return s==2 && v==0;
    if(!e && ~d[i][s][v])return d[i][s][v];
    int ans=0;
    int u=e?num[i]:9;
    for(int j=0; j<=u; j++)
    {
        int t=s;
        if(s==2)t=2;
        else if(s==1 && j==3)t=2;
        else if(s!=2 && j==1)t=1;
        else t=0;
        ans+=dp(i-1, t, (v*10+j)%13, e&&j==u);
    }
    return e?ans:d[i][s][v]=ans;
}

int main()
{
    while(~scanf("%d", &n))
    {
        cnt=0;
        while(n)
        {
            num[cnt++]=n%10;
            n/=10;
        }
        memset(d, -1, sizeof d);
        printf("%d\n", dp(cnt-1, 0, 0, 1));
    }
    return 0;
}
