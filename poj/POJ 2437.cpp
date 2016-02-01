#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cstring>
using namespace std;

struct Node
{
    int x, y;
    bool operator < (const Node a)const
    {
        return x<a.x;
    }
} node[11000];

int main()
{
    int n, len;
    while(~scanf("%d%d", &n, &len))
    {
        for(int i=0; i<n; i++)
            scanf("%d%d", &node[i].x, &node[i].y);
        sort(node, node+n);
        int L=0, R=0, ans=0;
        for(int i=0; i<n; i++)
        {
            L=max(node[i].x, L);
            R=max(node[i].y, R);
            if(L<R)
            {
                int t=(R-L+len-1)/len;
                ans+=t;
                L=R=t*len+L;
            }
        }
        printf("%d\n", ans);
    }
    return 0;
}
