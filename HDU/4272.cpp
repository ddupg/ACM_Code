#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cstring>
using namespace std;

int n, sta[1111];

int dfs(int u, int cnt)
{
    if(cnt==n)return 1;
    for(int i=u+1; i<n; i++)
    {
        int c=0;
        if(sta[i]!=-1)
        {
            c++;
            if(sta[i]==sta[u])
            {
                int t=sta[i];
                sta[i]=-1;
                for(int j=u+1; j<=n; j++)
                    if(sta[j]!=-1)
                    {
                        if(dfs(j, cnt+2))return 1;
                        break;
                    }
                sta[i]=t;
                break;
            }
        }
        if(c==6)
            return 0;
    }
    return 0;
}

int main()
{
    while(~scanf("%d", &n))
    {
        for(int i=0; i<n; i++)
            scanf("%d", &sta[i]);
        sta[n]=0;
        if(n & 1)
            puts("0");
        else if(dfs(0, 0))
            puts("1");
        else puts("0");
    }
    return 0;
}
