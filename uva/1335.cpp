#include <cstdio>
#include <algorithm>
using namespace std;

const int maxn=100000+10;
int n, r[maxn], left[maxn], right[maxn];

bool test(int p)
{
    int x=r[1], y=p-r[1];
    left[1]=r[1], right[1]=0;
    for(int i=2; i<=n; i++)
    {
        if(i&1)
        {
            right[i]=min(y-right[i-1], r[i]);
            left[i]=r[i]-right[i];
        }
        else
        {
            left[i]=min(x-left[i-1], r[i]);
            right[i]=r[i]-left[i];
        }
    }
    return left[n]==0;
}

int main()
{
    while(~scanf("%d", &n) && n)
    {
        for(int i=1; i<=n; i++)
            scanf("%d", r+i);
        r[n+1]=r[1];
        if(n==1)
        {
            printf("%d\n", r[1]);
            continue ;
        }

        int L=0, R=0;
        for(int i=1; i<=n; i++)
            L=max(L, r[i]+r[i+1]);

        if(n&1)
        {
            for(int i=1; i<=n; i++)
                R=max(R, r[i]*3);
            while(L<R)
            {
                int mid=L+(R-L)/2;
                if(test(mid))
                    R=mid;
                else L=mid+1;
            }
        }
        printf("%d\n", L);
    }
    return 0;
}
