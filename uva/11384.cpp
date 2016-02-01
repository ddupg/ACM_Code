#include <cstdio>

int main()
{
    int n;
    while(~scanf("%d", &n))
    {
        int ans=0;
        while(n)
            ++ans, n/=2;
        printf("%d\n", ans);
    }
    return 0;
}
