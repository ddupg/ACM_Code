#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
const int maxn=20;

int n, m, p[maxn], s[1<<17], d[1<<17], cover[1<<17], ALL;

int main()
{
    int kase=0;
    while(~scanf("%d", &n) && n)
    {
        ALL=(1<<n)-1;
        for(int i=0; i<n; i++)
        {
            p[i]=1<<i;
            scanf("%d", &m);
            while(m--)
            {
                int x;
                scanf("%d", &x);
                p[i]|=(1<<x);
            }
        }
        for(int s=0; s<(1<<n); s++)
        {
            cover[s]=0;
            for(int i=0; i<n; i++)
                if(1<<i&s)
                    cover[s]|=p[i];
        }
        for(int s=1; s<(1<<n); s++)
        {
            d[s]=0;
            for(int s0=s; s0; s0=s0-1&s)
                if(cover[s0]==ALL)
                    d[s]=max(d[s], d[s^s0]+1);
        }
        printf("Case %d: %d\n", ++kase, d[ALL]);
    }
    return 0;
}
