#include <cstdio>

int main()
{
    int n, k;
    scanf("%d%d", &n, &k);

    printf("%d\n", k*(n*6-1));
    for(int i=1; i<=n; i++)
        printf("%d %d %d %d\n", k*(i*6-5), k*(i*6-4), k*(i*6-3), k*(i*6-1));
    return 0;
}
