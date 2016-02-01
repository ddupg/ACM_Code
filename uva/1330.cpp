#include <cstdio>
#include <algorithm>
using namespace std;
const int maxn=1010;

int mat[maxn][maxn], up[maxn][maxn], left[maxn][maxn], right[maxn][maxn];
int n, m;

int main()
{
    int T;
    scanf("%d", &T);
    while(T--)
    {
        scanf("%d%d", &n, &m);
        for(int i=1; i<=n; i++)
            for(int j=1; j<=m; j++)
            {
                char c=getchar();
                while(c!='R' && c!='F')c=getchar();
                mat[i][j]=c=='F';
            }
        for(int i=1; i<=n; i++)
            for(int j=1; j<=m; j++)
                up[i][j]=mat[i][j]?up[i-1][j]+1:0;
        for(int i=1; i<=n; i++)
            left[i][1]=right[i][m]=0;
        for(int j=2; j<=m; j++)
            for(int i=1; i<=n; i++)
                left[i][j]=(up[i][j-1]>=up[i][j]?left[i][j-1]+1:0);
        for(int j=m-1; j>=1; j--)
            for(int i=1; i<=n; i++)
                right[i][j]=(up[i][j+1]>=up[i][j]?right[i][j+1]+1:0);
        int ans=0;
        for(int i=1; i<=n; i++)
            for(int j=1; j<=m; j++)
                ans=max(ans, up[i][j]*(1+left[i][j]+right[i][j]));
        printf("%d\n", 3*ans);
    }
    return 0;
}
