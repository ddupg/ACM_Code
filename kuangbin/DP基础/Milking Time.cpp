#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

struct Node
{
    int l, r, e;
    bool operator < (const Node a)const
    {
        return l<a.l;
    }
} nd[1100];

int main()
{
    int n, m, r, d[1100];
    while(~scanf("%d%d%d", &n, &m, &r))
    {
        for(int i=0; i<m; i++)
            scanf("%d%d%d", &nd[i].l, &nd[i].r, &nd[i].e);
        sort(nd, nd+m);
        int ans=0;
        for(int i=0; i<m; i++)
        {
            d[i]=nd[i].e;
            for(int j=0; j<i; j++)
                if(nd[j].r+r<=nd[i].l)
                    d[i]=max(d[i], d[j]+nd[i].e);
            ans=max(ans, d[i]);
        }
        printf("%d\n", ans);
    }
    return 0;
}
