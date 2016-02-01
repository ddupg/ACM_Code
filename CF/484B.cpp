#include <cstdio>
#include <algorithm>
using namespace std;
const int maxn=200000+10;

int a[maxn], n, Max;

int main()
{
    scanf("%d", &n);
    for(int i=0; i<n; i++)
    {
        scanf("%d", a+i);
        Max=max(a[i], Max);
    }
    sort(a, a+n);
    n=unique(a, a+n)-a;
    int ans=0;
    for(int i=0; i<n; i++)
        for(int j=2; a[i]*(j-1)<=Max; j++)
        {
            int k=lower_bound(a+i, a+n, j*a[i])-a;
            ans=max(ans, a[k-1]%a[i]);
        }
    printf("%d\n", ans);
    return 0;
}
