#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstdlib>
using namespace std;

int a[500000+100];

int cmp(const int& a, const int& b)
{
    return abs(a)<abs(b);
}

int main()
{
    int T, n;
    scanf("%d", &T);
    while(T--)
    {
        scanf("%d", &n);
        for(int i=0; i<n; i++)
            scanf("%d", a+i);

        sort(a, a+n, cmp);
        int ans=1;
        for(int i=1; i<n; i++)
            if(1LL*a[i]*a[i-1]<0)
                ans++;
        printf("%d\n", ans);
    }
    return 0;
}
