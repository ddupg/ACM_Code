#include <cstdio>
#include <cstring>
#include <algorithm>
#define clr(a, x) memset(a, x, sizeof a)
#define fst first
#define snd second
using namespace std;
typedef pair<int, int> pii;

const int maxn=808;
const int oo=0x3f3f3f3f;

pii x[maxn];
int n, d[maxn][maxn];

int main()
{
    int T;
    scanf("%d", &T);
    while(T--)
    {
        scanf("%d", &n);
        int sum=0;
        for(int i=1; i<=n; i++)
        {
            scanf("%d%d", &x[i].snd, &x[i].fst);
            sum+=x[i].snd;
        }
        sort(x+1, x+1+n);
        clr(d, 0x3f);
        d[1][1]=0;
        for(int i=1; i<n; i++)
            for(int j=0; j<=i; j++)if(d[i][j]<oo)
            {
                d[i+1][j+1]=min(d[i+1][j+1], d[i][j]);
                if(j)d[i+1][j-1]=min(d[i+1][j-1], d[i][j]+x[i+1].snd);
            }
        printf("%d\n", sum-d[n][0]);
    }
    return 0;
}
