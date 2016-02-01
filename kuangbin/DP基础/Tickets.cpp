#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

int n, d[2100], a[2100], b[2100];

int main()
{
    int T;
    scanf("%d", &T);
    while(T--)
    {
        scanf("%d", &n);
        for(int i=1; i<=n; i++)
            scanf("%d", a+i);
        for(int i=1; i<n; i++)
            scanf("%d", b+i);
        d[1]=a[1];
        for(int i=2; i<=n; i++)
            d[i]=min(d[i-1]+a[i], d[i-2]+b[i-1]);
        printf("%02d:%02d:%02d", 8+d[n]/3600, d[n]%3600/60, d[n]%60);
        if(8+d[n]/3600>=12)
            puts(" pm");
        else puts(" am");
    }
    return 0;
}
