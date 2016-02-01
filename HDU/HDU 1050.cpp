#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
const int maxn=220;

int main()
{
    int T;
    scanf("%d", &T);
    while(T--)
    {
        int n, cnt[maxn]={0}, ans=0, x, y;
        scanf("%d", &n);
        while(n--)
        {
            scanf("%d%d", &x, &y);
            x=x+1>>1;
            y=y+1>>1;
            if(x>y)
                swap(x, y);
            for(int i=x; i<=y; i++)
                ++cnt[i], ans=max(ans, cnt[i]);
        }
        printf("%d0\n", ans);
    }
    return 0;
}
