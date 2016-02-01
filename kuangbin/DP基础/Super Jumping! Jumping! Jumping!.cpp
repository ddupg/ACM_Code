#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn=1110;

int main()
{
    int n, a[maxn], d[maxn];
    while(~scanf("%d", &n) && n)
    {
        int ans=0;
        a[0]=d[0]=0;
        for(int i=1; i<=n; i++)
        {
            scanf("%d", a+i);
            ans=max(ans, d[i]=a[i]);
            for(int j=1; j<i; j++)
                if(a[j]<a[i])
                    ans=max(ans, d[i]=max(d[i], d[j]+a[i]));
        }
        printf("%d\n", ans);
    }
    return 0;
}
