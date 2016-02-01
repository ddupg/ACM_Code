#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <algorithm>
#include <fstream>
#include <set>
#include <map>
#include <queue>
#include <stack>
#include <list>
#include <vector>
#include <cmath>
#include <iomanip>
typedef long long LL;
typedef unsigned long long LLU;
const double PI=acos(-1.0);
using namespace std;
#define maxn 1000+10
int d[maxn][maxn];

int main()
{
    int m,n;
    while(scanf("%d%d",&m,&n) != EOF)
    {
        if(m == 0 && n == 0)
            break;
        int a[maxn],b[maxn], tar[maxn+maxn];
        memset(d,0,sizeof(d));

        for(int i = 1; i <= m; i++)
            scanf("%d",&a[i]);
        for(int j = 1; j <= n; j++)
            scanf("%d",&b[j]);
        for(int i = 1; i <= m+n; i++)
            scanf("%d",&tar[i]);

        d[0][0]=1;
        for(int i=0; i<=m; i++)
        {
            for(int j=0; j<=n; j++)
            {
                if(i>0)
                    d[i][j]=(d[i-1][j] && a[i]==tar[i+j]) || d[i][j];
                if(j>0)
                    d[i][j]=(d[i][j-1] && b[j]==tar[i+j]) || d[i][j];
            }
        }
        if(d[m][n])
            puts("possible");
        else
            puts("not possible");
    }
    return 0;
}
