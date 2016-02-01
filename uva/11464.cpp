#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
const int oo = 1e9;
const int maxn=20;
int n, A[maxn][maxn], B[maxn][maxn];

int dx[]={-1, 0, 0};
int dy[]={0, 1, -1};

int inside(int x, int y)
{
    if(x>=0 && x<n && y>=0 && y<n)return B[x][y];
    return 0;
}

int check(int s)
{
    memset(B, 0, sizeof(B));
    for(int i=0; i<n; i++)
    {
        if(s&(1<<i))B[0][i]=1;
        else if(A[0][i])return oo;
    }
    for(int i=1; i<n; i++)
        for(int j=0; j<n; j++)
        {
            int cnt=0;
            for(int k=0; k<3; k++)
            {
                int x=i-1+dx[k], y=j+dy[k];
                cnt+=inside(x, y);
            }
            if(A[i][j])B[i][j]=1;
            if((cnt&1) && !A[i][j])B[i][j]=1;
            if(!(cnt&1) && A[i][j])return oo;
        }
    int ans=0;
    for(int i=0; i<n; i++)
        for(int j=0; j<n; j++)
            ans+=(A[i][j]^B[i][j]);
    return ans;
}

int main()
{
    int T, kase=0;
    scanf("%d", &T);
    while(T--)
    {
        scanf("%d", &n);
        for(int i=0; i<n; i++)
            for(int j=0; j<n; j++)
                scanf("%d", &A[i][j]);
        int ans=oo;
        for(int i=0; i<(1<<n); i++)
            ans=min(ans, check(i));
        printf("Case %d: %d\n", ++kase, ans==oo?-1:ans);
    }
    return 0;
}
