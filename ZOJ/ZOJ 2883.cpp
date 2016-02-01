#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
using namespace std;
int p[22000];

int main()
{
    int T;
    scanf("%d", &T);
    while(T--)
    {
        int n;
        scanf("%d", &n);
        for(int i=0; i<n; i++)
            scanf("%d", p+i);
        sort(p, p+n);
        int cnt=0, ans=0;
        for(int i=n-1; i>=0; i--)
        {
            ++cnt;
            if(cnt%3==0)
                ans+=p[i];
        }
        printf("%d\n", ans);
    }
    return 0;
}
