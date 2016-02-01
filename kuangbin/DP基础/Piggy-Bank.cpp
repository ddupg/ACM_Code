#include <cstdio>
#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

int n, s, t, d[10010], p[550], w[550];

int main()
{
    int T;
    scanf("%d", &T);
    while(T--)
    {
        scanf("%d%d", &s, &t);
        scanf("%d", &n);
        for(int i=0; i<n; i++)
            scanf("%d%d", p+i, w+i);

        memset(d, 0x3f, sizeof d);
        d[s]=0;
        for(int i=s; i<=t; i++)
            for(int j=0; j<n; j++)
                if(i-s>=w[j])
                    d[i]=min(d[i], d[i-w[j]]+p[j]);
        if(d[t]==0x3f3f3f3f)
            puts("This is impossible.");
        else printf("The minimum amount of money in the piggy-bank is %d.\n", d[t]);
    }
    return 0;
}
