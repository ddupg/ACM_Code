#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;

struct Node
{
    int id, l;
    double f, d;
    bool operator < (const Node a)const
    {
        return d>a.d;
    }
} node[300000];

int n, m;

int main()
{
    while(~scanf("%d", &n))
    {
        for(int i=0; i<n; i++)
        {
            scanf("%d%d%lf", &node[i].id, &node[i].l, &node[i].f);
            node[i].d=node[i].f/node[i].l;
        }
        scanf("%d", &m);
        sort(node, node+n);
        printf("%d\n", node[m-1].id);
    }
    return 0;
}
