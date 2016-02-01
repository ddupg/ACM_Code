#include <iostream>
#include <cstring>
#include <cstdio>
#include <algorithm>
using namespace std;

int d[1200][1200], n, m;
char s1[2200], s2[2200];

int main()
{
    while(~scanf("%s%s", s1, s2))
    {
        memset(d, 0, sizeof d);
        n=strlen(s1), m=strlen(s2);
        for(int i=1; i<=n; i++)
            for(int j=1; j<=m; j++)
            {
                if(s1[i-1]==s2[j-1])
                    d[i][j]=d[i-1][j-1]+1;
                else
                    d[i][j]=max(d[i][j-1], d[i-1][j]);
            }
        printf("%d\n", d[n][m]);
    }
    return 0;
}
