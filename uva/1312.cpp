#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;

int n, w, h, x[120], y[120];

bool judge(int X, int Y, int len)
{
    if(X+len>w || Y+len>h)return false;
    for(int i=0; i<n; i++)
        if(x[i]>X && y[i]>Y && x[i]<X+len && y[i]<Y+len)
            return false;
    return true;
}

int main()
{
    int T;
    scanf("%d", &T);
    int a[120], b[120];
    while(T-- && ~scanf("%d%d%d", &n, &w, &h))
    {
        a[0]=b[0]=0;
        for(int i=0; i<n; i++)
        {
            scanf("%d%d", x+i, y+i);
            a[i+1]=x[i];
            b[i+1]=y[i];
        }
        sort(a, a+n+1);
        sort(b, b+n+1);
        int fir, sec, ans=0;
        for(int i=0; i<=n; i++)
            for(int j=0; j<=n; j++)
                if(judge(a[i], b[j], ans+1))
                {
                    int L=ans+1, R=min(w, h);
                    while(L<R)
                    {
                        int mid=(L+R+1)>>1;
                        if(judge(a[i], b[j], mid))
                            L=mid;
                        else R=mid-1;
                    }
                    ans=L;
                    fir=a[i];
                    sec=b[j];
                }
        printf("%d %d %d\n", fir, sec, ans);
        if(T)puts("");
    }
    return 0;
}
