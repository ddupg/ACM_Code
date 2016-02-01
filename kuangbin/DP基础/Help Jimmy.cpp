#include <cstdio>
#include <algorithm>
#include <iostream>
#include <cstring>
using namespace std;
const int maxn=1100;
const int oo=0x3f3f3f3f;

int n, x, y, limit, d[maxn][2];

struct Node
{
    int l, r, h;
    bool operator < (const Node a)const
    {
        return h>a.h;
    }
} nd[maxn];

int dp()
{
    memset(d, 0x3f, sizeof d);
    bool flag=true;
    for(int i=0; i<n; i++)
        if(y>=nd[i].h && y-nd[i].h<=limit && x>=nd[i].l && x<=nd[i].r)
        {
            d[i][0]=abs(nd[i].h-y)+abs(nd[i].l-x);
            d[i][1]=abs(nd[i].h-y)+abs(nd[i].r-x);
            flag=false;
            break;
        }
    if(flag)
        return y;
    for(int i=0; i<n; i++)
    {
        if(d[i][0]<oo)
            for(int j=i+1; j<n; j++)
                if(nd[i].h-nd[j].h<=limit && nd[i].h>nd[j].h && nd[i].l>=nd[j].l && nd[i].l<=nd[j].r)
                {
                    d[j][0]=min(d[j][0], d[i][0]+nd[i].h-nd[j].h+abs(nd[i].l-nd[j].l));
                    d[j][1]=min(d[j][1], d[i][0]+nd[i].h-nd[j].h+abs(nd[i].l-nd[j].r));
                    break;
                }
        if(d[i][1]<oo)
        {
            for(int j=i+1; j<n; j++)
                if(nd[i].h-nd[j].h<=limit && nd[i].h>nd[j].h && nd[i].r>=nd[j].l && nd[i].r<=nd[j].r)
                {
                    d[j][0]=min(d[j][0], d[i][1]+nd[i].h-nd[j].h+abs(nd[i].r-nd[j].l));
                    d[j][1]=min(d[j][1], d[i][1]+nd[i].h-nd[j].h+abs(nd[i].r-nd[j].r));
                    break;
                }
        }
    }

    int ans=oo;
    for(int i=0; i<n; i++)
        if(nd[i].h<=limit)
        {
            if(d[i][0]<oo)
            {
                bool flag=true;
                for(int j=i+1; j<n; j++)
                    if(nd[i].l>=nd[j].l && nd[i].l<=nd[j].r)
                    {
                        flag=0;
                        break;
                    }
                if(flag)
                    ans=min(ans, d[i][0]+nd[i].h);
            }
            if(d[i][1]<oo)
            {
                bool flag=true;
                for(int j=i+1; j<n; j++)
                    if(nd[i].r>=nd[j].l && nd[i].r<=nd[j].r)
                    {
                        flag=0;
                        break;
                    }
                if(flag)
                    ans=min(ans, d[i][1]+nd[i].h);
            }
        }
    return ans;
}

int main()
{
    int T;
    scanf("%d", &T);
    while(T--)
    {
        scanf("%d%d%d%d", &n, &x, &y, &limit);
        for(int i=0; i<n; i++)
            scanf("%d%d%d", &nd[i].l, &nd[i].r, &nd[i].h);
        sort(nd, nd+n);
        printf("%d\n", dp());
    }
    return 0;
}
