#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cstring>
using namespace std;

int main()
{
    int n;
    int cnt[110];
    while(scanf("%d", &n) && n)
    {
        memset(cnt, 0, sizeof(cnt));
        int Min=1e9;
        for(int i=0; i<n; i++)
        {
            int x;
            scanf("%d", &x);
            ++cnt[x];
            Min=min(Min, x);
        }
        printf("%d", Min);
        --cnt[Min];
        for(int i=0; i<=100; i++)
            while(cnt[i]--)
                printf(" %d", i);
        puts("");
    }
    return 0;
}
