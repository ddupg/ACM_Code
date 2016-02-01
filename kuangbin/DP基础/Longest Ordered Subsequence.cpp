#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

int main()
{
    int n, d[1110], a[1100];
    while(~scanf("%d", &n))
    {
        int ans=0;
        for(int i=0; i<n; i++)
        {
            scanf("%d", a+i);
            d[i]=1;
            for(int j=0; j<i; j++)
                if(a[i]>a[j])
                    d[i]=max(d[i], d[j]+1);
            ans=max(ans, d[i]);
        }
        printf("%d\n", ans);
    }
    return 0;
}
