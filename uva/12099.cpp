#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
using namespace std;
const int oo=0x3f3f3f3f;

struct Book
{
    int h, w;
    bool operator < (const Book b)const
    {
        return h>b.h;
    }
} book[100];
int n, d[2200][2200], m;

int dp()
{
    for(int j=0; j<=m; j++)
        for(int k=0; k<=m; k++)
            d[j][k]=oo;
    d[0][0]=0;
    int t=0;
    for(int i=1; i<n; i++)
    {
        t+=book[i].w;
        for(int j=t-book[1].w; j>=0; j--)
            for(int k=t-j-book[1].w; k>=0; k--)if(d[j][k]<oo)
                {
                    d[j+book[i+1].w][k]=min(d[j+book[i+1].w][k], d[j][k]+(j==0?book[i+1].h:0));
                    d[j][k+book[i+1].w]=min(d[j][k+book[i+1].w], d[j][k]+(k==0?book[i+1].h:0));
                }
    }

    int ans=oo;
    for(int i=1; i<=m-book[1].w; i++)
        for(int j=1; j<=m-i-book[1].w; j++)if(d[i][j]<oo)
                ans=min(ans, (book[1].h+d[i][j])*max(max(i, j), m-i-j));
    return ans;
}

int main()
{
    int T;
    scanf("%d", &T);
    while(T--)
    {
        scanf("%d", &n);
        m=0;
        for(int i=1; i<=n; i++)
        {
            scanf("%d%d", &book[i].h, &book[i].w);
            m+=book[i].w;
        }
        sort(book+1, book+1+n);
        printf("%d\n", dp());
    }
    return 0;
}
