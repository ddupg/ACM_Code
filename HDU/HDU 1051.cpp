#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
using namespace std;

struct Node
{
    int x, y;
    bool operator <(const Node a)const
    {
        return x<a.x || (x==a.x && y<a.y);
    }
}p[5500];

int main()
{
    int n, T;
    scanf("%d", &T);
    while(T-- && ~scanf("%d", &n))
    {
        for(int i=0; i<n; i++)
            scanf("%d%d", &p[i].x, &p[i].y);
        sort(p, p+n);
        int cnt=n, ans=0;
        while(true)
        {
            if(!cnt)break;
            ++ans;
            int x=p[0].x, y=p[0].y;
            int tmp=0;
            for(int i=1; i<cnt; i++)
            {
                if(p[i].x>=x && p[i].y>=y)
                    x=p[i].x, y=p[i].y;
                else p[tmp++]=p[i];
            }
            cnt=tmp;
        }
        printf("%d\n", ans);
    }
    return 0;
}
