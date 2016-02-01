#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>
using namespace std;
const int maxn=110;

int main()
{
    int n, c, sz[maxn], cnt=0, Max=0, Min=1e9;
    vector<int> ans[maxn];
    bool fil[maxn]= {0};
    scanf("%d%d", &n, &c);
    for(int i=1; i<=n; i++)
    {
        scanf("%d", sz+i);
        Min=min(sz[i], Min);
        Max=max(Max, sz[i]);
    }
    if(Max-Min>c)
    {
        puts("NO");
        return 0;
    }
    for(int i=1; i<=c; i++)
    {
        bool flag=0;
        while(cnt<n && !flag)
            for(int j=1; j<=n; j++)
            {
                if(fil[j])flag=true ;
                else if(sz[j]==ans[j].size())
                    cnt++, fil[j]=flag=true;
                else ans[j].push_back(i);
            }
    }
    puts("YES");
    for(int i=1; i<=n; i++)
    {
        printf("%d", ans[i][0]);
        for(int j=1; j<ans[i].size(); j++)
            printf(" %d", ans[i][j]);
        puts("");
    }
    return 0;
}
