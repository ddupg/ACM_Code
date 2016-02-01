#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
using namespace std;

int main()
{
    int n, T;
    scanf("%d", &T);
    while(T-- && scanf("%d", &n))
    {
        int x, Max, ans=-1e9;
        scanf("%d", &Max);
        while(--n)
        {
            scanf("%d", &x);
            ans=max(Max-x, ans);
            Max=max(Max, x);
        }
        printf("%d\n", ans);
    }
    return 0;
}
